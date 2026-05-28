/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:52:33 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/28 16:18:18 by ethutin-         ###   ########.fr       */
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
