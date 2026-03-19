/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extend_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 21:08:20 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/12 11:59:13 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->path)
			free_arr(data->path);
		if (data->cmd_split)
			free_arr(data->cmd_split);
		free(data);
	}
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		data_malloc_error(data);
	return (data);
}

void	full_cmd(t_data *data, char *command, int i)
{
	char	*tmp;

	while (data->path && data->path[++i])
	{
		if (data->path[i][0] == '\0')
			tmp = ft_strdup("./");
		else
			tmp = ft_strjoin(data->path[i], "/");
		if (!tmp)
			data_malloc_error(data);
		data->path_and_cmd = ft_strjoin(tmp, command);
		free(tmp);
		if (!data->path_and_cmd)
			data_malloc_error(data);
		if (access(data->path_and_cmd, F_OK | X_OK) == 0)
			return ;
		free(data->path_and_cmd);
	}
	data->cmd_invalid = 1;
}
