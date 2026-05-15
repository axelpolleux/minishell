/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/14 15:00:48 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_data *data, t_cmd *cmd, char **env)
{
	if (execve(cmd->cmd_path, cmd->cmd, env) == -1)
	{
		free_arr(env);
		perror("minishell");
		if (errno == ENOENT)
			data->exit = 127;
		else if (errno == EACCES)
			data->exit = 126;
		else
			data->exit = 1;
		exit (data->exit);
	}
	free_arr(env);
}

void	children(t_data *data, t_cmd *cmd)
{
	char	**env;

	if (is_builtin(data->built_in, cmd->cmd[0]))
		built_child(data, cmd);
	else if (!check_cmd(data, cmd))
	{
		manage_redir(data, cmd);
		if (cmd->next)
			close (data->fd_storage[1]);
		if (cmd->input != STDIN_FILENO && cmd->input >= 0)
			close(cmd->input);
		if (cmd->next)
			close(data->fd_storage[0]);
		env = tab_env(data->t_env, -1);
		if (!env)
			data_malloc_error(data);
		exec_command(data, cmd, env);
	}
	exit(data->exit);
}

void	parent(t_data *data, t_cmd *cmd)
{
	close(data->fd_storage[1]);
	if (cmd->next)
		cmd->next->input = data->fd_storage[0];
	else
		close(data->fd_storage[0]);
}

void	manage_process(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->prev)
			get_expand(data, cmd);
		if (data->pipe-- > 0)
			if (pipe(data->fd_storage) == -1)
				pipe_error(data);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			fork_error(data);
		else if (data->pid[i] == 0)
			children(data, cmd);
		else
			parent(data, cmd);
		cmd = cmd->next;
		i++;
	}
}

void	exec(t_data *data)
{
	t_cmd	*t_cmd;
	int		count;

	t_cmd = data->cmd;
	get_expand(data, t_cmd);
	if (is_builtin(data->built_in, t_cmd->cmd[0]) && !t_cmd->next)
	{
		exec_built(data, t_cmd);
		return ;
	}
	count = ft_lstsize_c(t_cmd);
	data->pid = ft_calloc(sizeof(pid_t), count);
	if (!data->pid)
		data_malloc_error(data);
	heredoc_manage(data->cmd);
	manage_process(data, t_cmd);
	wait_end(data, count);
}
