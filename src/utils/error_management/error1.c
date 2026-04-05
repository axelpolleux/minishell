/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:51:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/05 16:31:48 by ethutin-         ###   ########.fr       */
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

int	open_error(t_data *data)
{
	closes(-1, data->fd_storage);
	write(2, "minishell: ", 12);
	perror(data->cmd->cmd[1]);
	free_data(data);
	exit(EXIT_FAILURE);
}

void	wait_error(t_data *data)
{
	free_data(data);
	perror("waitpid");
	exit (-1);
}

void	dup_error(t_data *data)
{
	free_data(data);
	perror("dup");
	exit (-1);
}

void	fork_error(t_data *data)
{
	free_data(data);
	perror("fork");
	exit (-1);
}
