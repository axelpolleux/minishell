/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:26:35 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/05 16:52:42 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	data_malloc_error(t_data *data)
{
	if (data)
		free_data(data);
	write(2, "Error : A malloc has failed.\n", 29);
	exit (EXIT_FAILURE);
}

// void	error_exit(t_data *data)
// {
// 	if (data->error_exit > -2)
// 	{
// 		perror(data->error_line);
// 		exit(data->error_exit);
// 	}
// }

void	pipe_error(t_data *data)
{
	perror("pipe");
	free_data(data);
	exit (-1);
}
