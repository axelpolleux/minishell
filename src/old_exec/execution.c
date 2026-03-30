/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/30 18:44:10 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_command(t_data *data, char  **env)
// {
//     if (execve(data->cmd->cmd_path, data->cmd->cmd, env) == -1)
// 	{
// 		free_arr(env);
// 		perror("minishell");
// 		free_data(data);
// 		if (errno == ENOENT)
// 			exit(127);
// 		else if (errno == EACCES)
// 			exit(126);
// 		else
// 			exit(1);
// 	}
// 	free_arr(env);
// }

// void	parent(t_data *data, int i)
// {
// 	data->last_fd = -1;
// 	while (data->cmd)
// 	{
// 		data->fd_storage[0] = -1;
// 		data->fd_storage[1] = -1;
// 		if (data->cmd->next)
// 			if (pipe(data->fd_storage) == -1)
// 				pipe_error(data);
// 		data->pid[i] = fork();
// 		if (data->pid[i] == -1)
// 			exit(EXIT_FAILURE);
// 		if (data->pid[i] == 0)
// 			children(data);
// 		if (data->last_fd != -1)
// 			close(data->last_fd);
// 		if (data->cmd)
// 		{
// 			close(data->fd_storage[1]);
// 			data->last_fd = data->fd_storage[0];
// 		}
// 		data->cmd = data->cmd->next;
// 	}
// 	if (data->last_fd != -1)
// 		close(data->last_fd);
// }

// void	children(t_data *data)
// {
// 	char **env;

// 	if (!here_doc_manage(data))
	
// 	// {
	
// 	// 	data->fd = verif_file(av[1], 0, 0);
// 	// 	if (data->fd == -1)
// 	// 		open_error(data, av, 1);
// 	// 	if (dup2(data->fd, 0) == -1)
// 	// 		exit(EXIT_FAILURE);
// 	// 	close(data->fd);
// 	// }

	
// 	if (dup2(data->last_fd, 0) == -1)
// 		exit(EXIT_FAILURE);
// 	close(data->last_fd);
// 	tennage(data);
// 	if (data->cmd->type == CMD)
// 		get_cmd_path(data);
// 		env = tab_env(data->t_env);
// 	if(!env)
// 		data_malloc_error(data);
// 	exec_command(data, env);
// }

// void	exec(t_data *data)
// {
// 	int	i;
// 	int	pid;
// 	int	error;

// 	pid =  nb_process(data->cmd);
// 	// if (!pid)
//     // return ();
// 	data->pid = ft_calloc(sizeof(pid_t), pid);
// 	if (!data->pid)
// 		data_malloc_error(data);
// 	parent(data, &i);
// 	i = -1;
// 	while (++i < ft_lstsize_c(data->cmd) - 1)
// 		waitpid(data->pid[i], &error, 0);
// 	free_data(data);
// 	if (WIFEXITED(error))
// 		exit(WEXITSTATUS(error));
// }
