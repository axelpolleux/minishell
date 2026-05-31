/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:52:33 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/31 22:27:32 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	history_heredoc(t_data *data, char *line, int *fd)
{
	char	*tmp;

	tmp = ft_strjoin(data->history, line);
	free(data->history);
	if (!tmp)
	{
		closes(-1, fd);
		free(line);
		return (true);
	}
	data->history = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!data->history)
	{
		closes(-1, fd);
		free(line);
		return (true);
	}
	add_history(data->history);
	return (false);
}

bool	write_here(t_redir_her *doc, char *line, int *fd)
{
	if (!ft_strcmp(line, doc->file))
	{
		free(line);
		return (true);
	}
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	free(line);
	return (false);
}

char	*define_line(t_data *data, int *index)
{
	char	*res;

	res = ft_strdup("");
	data->quote = NQUOT;
	*index = 0;
	return (res);
}

void	heredoc_eof_error(t_redir_her *doc, int fd)
{
	ft_putstr_fd("minichevre: warning: wrong EOF (wanted `", 2);
	ft_putstr_fd(doc->file, 2);
	ft_putstr_fd("`)\n", 2);
	close(*fd[1]);
}
