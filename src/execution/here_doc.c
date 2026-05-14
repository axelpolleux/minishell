/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 15:16:58 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/02 11:53:36 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_enof(t_data *data, char *line)
{
	if (!ft_strncmp(line, data->cmd->cmd[1], ft_strlen(data->cmd->cmd[1]))
		&& line[ft_strlen(data->cmd->cmd[1])] == '\n')
	{
		get_next_line(-1, 0);
		free(line);
		return (1);
	}
	return (0);
}

void	in_hre(t_data *data, int fd[2])
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0, 0);
		if (!line)
			exit(0);
		if (get_enof(data, line))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

int	hre_arg(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmd;
	if (!tmp->cmd[1])
	{
		error_perror(SYNT_ER, P_ERROR, 2);
		exit(2);
	}
	if (only_quote(tmp->cmd[1]))
	{
		if (data->cmd->cmd[1])
			free(data->cmd->cmd[1]);
		data->cmd->cmd[1] = ft_strdup("\n");
		if (!data->cmd->cmd[1])
			return (-1);
	}
	return (1);
}

int	here_doc_manage(t_data *data)// tout et a refaire 
{
	int		fd[2];
	int		error;

	if (data->cmd->type != HEREDOC)
		return (0);
	if (pipe(fd) == -1)
		pipe_error(data);
	error = hre_arg(data);
	if (error == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else if (error == -1)
		data_malloc_error(data);
	else
		in_hre(data, fd);
	return (1);
}
