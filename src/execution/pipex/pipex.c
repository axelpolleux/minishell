/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/12 11:59:01 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	command_1(char **av, char **env, t_data *data)
{
	int		fd;

	fd = verif_file(av[1], 0);
	if (fd == -1)
		open_error(data, av, 1);
	get_cmd_path(av[2], env, data);
	dup2(fd, 0);
	dup2(data->fd_storage[1], 1);
	closes(fd, data->fd_storage);
	exec_command(env, data);
}

void	command_2(char **av, char **env, t_data *data)
{
	int		fd;

	fd = verif_file(av[4], 1);
	if (fd == -1)
		open_error(data, av, 4);
	get_cmd_path(av[3], env, data);
	dup2(fd, 1);
	dup2(data->fd_storage[0], 0);
	closes(fd, data->fd_storage);
	exec_command(env, data);
}

void	process_manage(t_data *data, char **env, char **av)
{
	int		error[2];

	data->pid[0] = fork();
	if (data->pid[0] == -1)
		exit(-1);
	if (!data->pid[0])
	{
		command_1(av, env, data);
		exit(1);
	}
	data->pid[1] = fork();
	if (data->pid[1] == -1)
		exit(-1);
	if (!data->pid[1])
	{
		command_2(av, env, data);
		exit(1);
	}
	closes(-1, data->fd_storage);
	waitpid(data->pid[0], &error[0], 0);
	waitpid(data->pid[1], &error[1], 0);
	free_data(data);
	if (WIFEXITED(error[1]))
		exit(WEXITSTATUS(error[1]));
}
