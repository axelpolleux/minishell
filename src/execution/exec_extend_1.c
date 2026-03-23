/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 21:08:20 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/23 15:22:58 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		data_malloc_error(data);
	data->fd_storage[0] = -1;
	data->fd_storage[1] = -1;
	data->last_fd = -1;
	data->ac = ac;
	data->cmd_n = 0;
	data->st_env = NULL;
	data->av = av;
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

void	here_doc_manage(t_data *data)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		pipe_error(data);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line_e(0, 0);
		if (!line)
			exit(0);
		if (!ft_strncmp(line, data->limit, ft_strlen(data->limit))
			&& line[ft_strlen(data->limit)] == '\n')
		{
			get_next_line_e(-1, 0);
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	tennage(t_data *data, char **av)
{
	if (data->cmd_n == data->ac - data->start - 2)
	{
		data->fd = verif_file(av[data->ac - 1], 1, data->doc);
		if (data->fd == -1)
			open_error(data, av, data->ac - 1);
		if (dup2(data->fd, 1) == -1)
			exit(EXIT_FAILURE);
		close(data->fd);
	}
	else
	{
		if (dup2(data->fd_storage[1], 1) == -1)
			exit(EXIT_FAILURE);
		closes(-1, data->fd_storage);
	}
	closes(data->last_fd, data->fd_storage);
}
