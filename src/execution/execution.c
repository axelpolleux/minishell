/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/31 14:27:19 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_data *data, char  **env)
{
	if (execve(data->cmd->cmd_path, data->cmd->cmd, env) == -1)
	{
		free_arr(env);
		perror("minishell");
		free_data(data);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(1);
	}
	free_arr(env);
}

void manage_redir(t_cmd *cmd)
{
	if (!cmd->input)
	{
		dup2(cmd->input, STDIN_FILENO);
		close(cmd->input);
	}
	if (!cmd->output)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->output);
	}
}


void children(t_data *data, t_cmd *cmd)
{
	char **env;

	if (data->last_fd != -1)
	{
		dup2(data->last_fd, STDIN_FILENO);
		close(data->last_fd);
	}
	if (cmd->next)
	{
		dup2(data->fd_storage[1], STDOUT_FILENO);
		close(data->fd_storage[0]);
		close(data->fd_storage[1]);
	}
	manage_redir(cmd);
	// if (is_builtin(data->built_in, cmd->cmd[0]))
	//     exit(children_built(data, cmd));
	get_cmd_path(data); //// afaire de plus vois bien a l'utilisation du fd de la struct, t'afait de la merde a se niveaux la pendant le reforg
	env = tab_env(data->t_env);
	if (!env)
		data_malloc_error(data);
	exec_command(data, env);
}


void parent(t_data *data, int i)
{
	t_cmd *cmd;

	data->last_fd = -1;
	cmd = data->cmd;
	while (cmd)
	{
		data->fd_storage[0] = -1;
		data->fd_storage[1] = -1;
		if (cmd->next && pipe(data->fd_storage) == -1) //la secu et l'error a revoir
			perror("METAL PIPE"); // a remplacer pipe_error()
		data->pid[i] = fork();
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
	}
}

void wait_end(t_data *data, int count)
{
	int i;
	int error;

	i = 0;
	while (i < count)
	{
		waitpid(data->pid[i], &error, 0);
		i++;
	}
	free_data(data);
	if (WIFEXITED(error))
		exit(WEXITSTATUS(error));
}

void exec(t_data *data)
{
	int count;

	count = nb_process(data->cmd);
	if (count == 0)
		return ;
	data->pid = ft_calloc(sizeof(pid_t), count);
	if (!data->pid)
		data_malloc_error(data);
	if (count == 1 && is_builtin(data->built_in, data->cmd->cmd[0]))
		return ;//parent_built(data);
	else
		parent(data, -1);
	wait_end(data, count);
}
