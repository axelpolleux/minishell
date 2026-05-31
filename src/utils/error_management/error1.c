/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:51:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/27 15:10:40 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_error(t_data *data)
{
	closes(-1, data->fd_storage);
	ft_putendl_fd("minichevre: ", 2);
	perror(data->cmd->args[0]);
	free_data(data);
	exit(EXIT_FAILURE);
}

void	wait_error(t_data *data)
{
	free_data(data);
	perror("waitpid");
	exit (1);
}

void	dup_error(t_data *data)
{
	free_data(data);
	perror("dup");
	exit (1);
}

void	fork_error(t_data *data)
{
	free_data(data);
	perror("fork");
	exit (1);
}

int	error_pars(int error)
{
	if (!error)
		ft_putstr_fd(QUOT_ER, 2);
	else if (error)
		ft_putstr_fd(SYNT_UT, 2);
	return (EXIT_FAILURE);
}
