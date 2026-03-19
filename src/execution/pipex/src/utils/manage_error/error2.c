/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:26:35 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/12 11:57:13 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	data_malloc_error(t_data *data)
{
	if (data)
		free_data(data);
	write(2, "Error : A malloc has failed.\n", 29);
	exit (EXIT_FAILURE);
}

void	void_path(t_data *data)
{
	char	*msg;

	msg = ft_strjoin(data->cmd_split[0], ": command not found\n");
	if (!msg)
		data_malloc_error(data);
	write(2, msg, strlen(msg));
	free(msg);
	free_data(data);
	exit(127);
}

void	null_path(t_data *data)
{
	char	*msg;
	char	*tmp;

	tmp = ft_strjoin("pipex: no such file or directory: ",
			data->cmd_split[0]);
	if (!tmp)
		data_malloc_error(data);
	msg = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!msg)
		data_malloc_error(data);
	write(2, msg, strlen(msg));
	free(msg);
	free_data(data);
	exit(127);
}
