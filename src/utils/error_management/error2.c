/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:26:35 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/14 15:05:31 by ethutin-         ###   ########.fr       */
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

void	error_exit(char *error, int error_p, int fd)
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

void	error_export(t_data *data, char *error)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin("minishell: export: `", error);
	if (!tmp)
		data_malloc_error(data);
	line = ft_strjoin(tmp, "`: not a valid identifier\n");
	free(tmp);
	if (!line)
		data_malloc_error(data);
	ft_putstr_fd(line, 2);
	free(line);
}
