/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/30 11:36:36 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_data *data, char **env)
{
	if (execve(data->cmd->cmd_path, data->cmd->cmd, env) == -1)
	{
		free_arr(env);
		perror("minishell");
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(1);
	}
}

void	children(t_data *data, t_cmd *cmd)
{
	char	**env;

	if (is_builtin(data->built_in, cmd->cmd[0]))
		exit(exec_built(data, cmd));
	get_cmd_path(data, cmd);
	if (data->exit > -2) // le -2 et pour sigaler la premier fois
		exit(data->exit);
	if (data->last_fd != -1)
	{
		if (dup2(data->last_fd, STDIN_FILENO) == -1)
			dup_error(data);
		close(data->last_fd);
	}
	if (cmd->next)
	{
		if (dup2(data->fd_storage[1], STDOUT_FILENO) == -1)
			dup_error(data);
		closes(-1, data->fd_storage);
	}
	manage_redir(data, cmd);
	env = tab_env(data->t_env, -1);
	if (!env)
		data_malloc_error(data);
	exec_command(data, env);
	free_arr(env);
}

void	parent(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	data->last_fd = -1;
	while (cmd)
	{
		if (cmd->type == PIPE)
			if (pipe(data->fd_storage) == -1)
				pipe_error(data);//a amelioer pour faire un semi heredoc pour pipe end
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			fork_error(data);
		if (data->pid[i] == 0)
			children(data, cmd);
		if (data->last_fd != -1)
			close(data->last_fd);
		if (cmd->next)
		{
			close(data->fd_storage[1]);
			data->last_fd = data->fd_storage[0];
		}
		cmd = cmd->next;
		i++;
	}
}

void	wait_end(t_data *data, int count)
{
	int	i;
	int	error;

	i = -1;
	while (++i < count)
		if (waitpid(data->pid[i], &error, 0) == -1)
			wait_error(data);
	free_data(data);
	if (WIFEXITED(error))
		exit(WEXITSTATUS(error));
}

void	exec(t_data *data)
{
	t_cmd	*t_cmd;
	int		count;

	t_cmd = data->cmd;
	count = nb_process(t_cmd);
	if (count == 0)
		return ;
	data->pid = ft_calloc(sizeof(pid_t), count); //pas sur
	if (!data->pid)
		data_malloc_error(data);
	if (is_builtin(data->built_in, t_cmd->cmd[0]) && !t_cmd->next)
		exit(exec_built(data, t_cmd));
	parent(data, t_cmd);
	wait_end(data, count);
}
