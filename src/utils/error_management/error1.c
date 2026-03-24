/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:51:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/24 13:54:03 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_error(char **path)
{
	if (path)
		free_arr(path);
	write(2, "Error : A malloc has failed.\n", 29);
	exit (EXIT_FAILURE);
}

int	open_error(t_data *data, char **av, int cmd)
{
	char	*msg;
	char	*tmp;

	closes(-1, data->fd_storage);
	msg = ft_strjoin(av[cmd], " \n");
	if (!msg)
		data_malloc_error(data);
	tmp = ft_strjoin(": ", msg);
	free(msg);
	if (!tmp)
		data_malloc_error(data);
	msg = ft_strjoin(strerror(errno), tmp);
	free(tmp);
	if (!msg)
		data_malloc_error(data);
	tmp = ft_strjoin("pipex: ", msg);
	free(msg);
	if (!tmp)
		data_malloc_error(data);
	write(2, tmp, strlen(tmp));
	free(tmp);
	free_data(data);
	exit(EXIT_FAILURE);
}

// void	command_error(t_data *data)
// {
// 	char	*msg;
// 	char	*tmp;

// 	if (data->cmd_space_void)
// 		tmp = ft_strjoin(data->cmd_space_void, "\n");
// 	else
// 		tmp = ft_strjoin(data->token->cmd_part[0], "\n");
// 	if (!tmp)
// 		data_malloc_error(data);
// 	msg = ft_strjoin("pipex: command not found: ", tmp);
// 	free(tmp);
// 	if (!msg)
// 		data_malloc_error(data);
// 	write(2, msg, strlen(msg));
// 	free(msg);
// 	free_data(data);
// 	exit(127);
// }

void	null_command(t_data *data)
{
	write(2, "pipex: permission denied: \n", 27);
	free_data(data);
	exit(126);
}
