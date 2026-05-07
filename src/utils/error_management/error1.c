/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:51:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/07 18:05:13 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_error(t_data *data)
{
	// closes(-1, data->fd_storage);
	write(2, "minishell: ", 12);
	perror(&data->cmd->command[1]);
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

void	error_quote(void)
{
	ft_putstr_fd(QUOT_ER, 2);
	exit (0);
}
