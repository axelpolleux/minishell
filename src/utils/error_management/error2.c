/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:26:35 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 17:52:47 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	data_malloc_error(t_data *data)
{
	if (data)
		free_data(data);
	ft_putstr_fd(DATA_ER, 2);
	exit (EXIT_FAILURE);
}

//refaire la gestion d'erreru en utilsant aue error_perror et error_exit
void	error_perror(char *error, int error_p, int fd)
{
	if (error_p)
		perror("error");
	else
		ft_putstr_fd(error, fd);
}

void	pipe_error(t_data *data)
{
	perror("pipe");
	free_data(data);
	exit (-1);
}

void	error_export(char *error)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
}

void	error_exit(t_data *data, char *error)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_data(data);
	exit(0);
}
