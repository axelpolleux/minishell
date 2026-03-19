/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/18 13:42:22 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_command(char **env, t_data *data)
{
	if (data->path_void)
		void_path(data);
	if (data->path_null || data->path_invalid)
		null_path(data);
	if (data->cmd_null)
		null_command(data);
	else if (data->cmd_invalid)
		command_error(data);
	if (execve(data->path_and_cmd, data->cmd_split, env) == -1)
	{
		perror("pipex");
		free_data(data);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(1);
	}
}

void	parent(char **av, char **env, t_data *data)
{
	data->last_fd = -1;
	while (data->cmd_n < (data->ac - data->start - 1))
	{
		data->fd_storage[0] = -1;
		data->fd_storage[1] = -1;
		if (data->cmd_n < data->ac - 4)
			if (pipe(data->fd_storage) == -1)
				pipe_error(data);
		data->pid[data->cmd_n] = fork();
		if (data->pid[data->cmd_n] == -1)
			exit(EXIT_FAILURE);
		if (data->pid[data->cmd_n] == 0)
			children(data, av, env);
		if (data->last_fd != -1)
			close(data->last_fd);
		if (data->cmd_n < data->ac - 4)
		{
			close(data->fd_storage[1]);
			data->last_fd = data->fd_storage[0];
		}
		data->cmd_n++;
	}
	if (data->last_fd != -1)
		close(data->last_fd);
}

void	children(t_data *data, char **av, char **env)
{
	if (data->cmd_n == 0)
	{
		if (data->doc)
			here_doc_manage(data);
		else
		{
			data->fd = verif_file(av[1], 0, 0);
			if (data->fd == -1)
				open_error(data, av, 1);
			if (dup2(data->fd, 0) == -1)
				exit(EXIT_FAILURE);
			close(data->fd);
		}
	}
	else
	{
		if (dup2(data->last_fd, 0) == -1)
			exit(EXIT_FAILURE);
		close(data->last_fd);
	}
	tennage(data, av);
	get_cmd_path(av[data->start + data->cmd_n], env, data);
	exec_command(env, data);
}

void	process_manage(t_data *data, char **env, char **av)
{
	int	i;
	int	error;

	parent(av, env, data);
	i = 0;
	while (i < data->ac - data->start - 1)
	{
		waitpid(data->pid[i], &error, 0);
		i++;
	}
	free_data(data);
	if (WIFEXITED(error))
		exit(WEXITSTATUS(error));
}
