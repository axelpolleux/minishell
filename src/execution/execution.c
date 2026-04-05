/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/05 16:48:10 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void manage_redir(t_data *data, t_cmd *cmd)
{
	if (cmd->input != -1)
	{
		if (dup2(cmd->input, STDIN_FILENO) == -1)
			dup_error(data);
		close(cmd->input);
	}
	if (cmd->output != -1)
	{
		if (dup2(cmd->output, STDOUT_FILENO) == -1)
			dup_error(data);		
		close(cmd->output);
	}
}

void exec_command(t_data *data, char **env)
{
	if(execve(data->cmd->cmd_path, data->cmd->cmd, env) == -1)
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

void children(t_data *data, t_cmd *cmd, int last_fd)
{
	char **env;

	// if (is_builtin(data->built_in, cmd->cmd[0]))
	// 	exec_built(data, cmd);
	get_cmd_path(data, cmd);
	if (data->error_exit > -2) //error_exit(data);
		exit(data->error_exit);
	if (last_fd != -1)
	{
		if (dup2(last_fd, STDIN_FILENO) == -1)
			dup_error(data);
		close(last_fd);
	}
	if (cmd->next)
	{
		if (dup2(data->fd_storage[1], STDOUT_FILENO) == -1)
			dup_error(data);
		closes(-1, data->fd_storage);
	}
	manage_redir(data, cmd);
	env = tab_env(data->t_env);
	if (!env)
		data_malloc_error(data);
	exec_command(data, env);
	free_arr(env);
}

void	parent(t_data *data, t_cmd *cmd)
{
	int	i;
	int last_fd;

	i = 0;
	last_fd = -1;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(data->fd_storage) == -1)
				pipe_error(data);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			fork_error(data);
		if (!data->pid[i])
			children(data, cmd, last_fd);
		if (last_fd != -1)
			close(last_fd);
		if (cmd->next)
		{		
			close(data->fd_storage[1]);
			last_fd = data->fd_storage[0];
		}
		cmd = cmd->next;
		i++;
	}
}

void wait_end(t_data *data, int count)
{
	int i;
	int error;

	i = -1;
	while (++i < count)
		if (waitpid(data->pid[i], &error, 0) == -1)
			wait_error(data);
	free_data(data);
	if (WIFEXITED(error))
		exit(WEXITSTATUS(error));
}

void exec(t_data *data)
{
	t_cmd	*cmd;
	int		count;

	cmd = data->cmd;
	count = nb_process(cmd);
	if (count == 0)
		return ;
	data->pid = ft_calloc(sizeof(pid_t), count);
	if (!data->pid)
		data_malloc_error(data);
	// if (is_builtin(data->built_in, cmd->cmd[0]) && !cmd->next)
	// 	exec_built(data, cmd);// pas enocre terminer
	parent(data, cmd);
	wait_end(data, count);
}

/*
void parent(t_data *data, t_cmd *cmd)
{
	int	i;

	data->last_fd = -1;
	i = 0;
	while (cmd)
	{
		if (cmd->next && pipe(data->fd_storage) == -1)
			pipe_error(data);
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
*/
/*
void parent(t_data *data, t_cmd *cmd)
{
	close(data->fd_storage[1]);
	if (cmd->input >= 0) // tester > 2
		close(cmd->input);
	// if (cmd->input == -1)
	// 	cmd->input = data->fd_storage[0];
	// if (cmd->next && cmd->next->input == -1)
	// 	cmd->next->input = data->fd_storage[0];
	else
		close(data->fd_storage[0]);
}
*/