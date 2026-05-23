/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:15 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/23 13:46:35 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	new_delimiter(t_data *data, t_redir_her *doc)
{
	char	*n_line;
	int		i;

	data->quote = NQUOT;
	n_line = ft_strdup("");
	if (!n_line)
		return (true);
	i = 0;
	while (doc->file[i])
	{
		if (quote_expand(data, doc->file, &i))
			continue ;
		n_line = ft_charjoin(n_line, doc->file[i]);
		if (!n_line)
			return (true);
		i++;
	}
	free(doc->file);
	doc->file = n_line;
	if (!doc->file)
		return (true);
	return (false);
}

bool	read_heredoc(t_data *data, t_redir_her *doc, char *tmp, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[1]);
			break ;
		}
		if (history_heredoc(data, line, fd))
			return (true);
		line = expand_here_doc(data, doc, line, tmp);
		if (!line)
		{
			closes(-1, fd);
			return (true);
		}
		if (write_here(doc, line, fd))
			break ;
	}
	return (false);
}

int	init_heredoc(t_data *data, t_redir_her *doc)
{
	char	*tmp;
	int		fd[2];

	tmp = ft_strdup(doc->file);
	if (!tmp)
		return (-2);
	if (pipe(fd) == -1)
		return (-1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	printf("old_delim:{%s}\n", doc->file);
	if (new_delimiter(data, doc))
	{
		free(tmp);
		return (-2);
	}
	printf("new_delim:{%s}\n", doc->file);
	if (read_heredoc(data, doc, tmp, fd))
	{
		free(tmp);
		return (-2);
	}
	free(tmp);
	close(fd[1]);
	return (fd[0]);
}

bool	heredoc_manage(t_data *data, t_cmd *cmd)
{
	t_redir_her	*doc;

	if (data->history)
		free(data->history);
	data->history = ft_strjoin(data->line, "\n");
	if (!data->history)
		return (true);
	while (cmd)
	{
		doc = cmd->redir;
		while (doc)
		{
			if (doc->type == HEREDOC)
			{
				doc->fd = init_heredoc(data, doc);
				if (doc->fd == -2)
					return (true);
				cmd->input = doc->fd;
			}
			doc = doc->next;
		}
		cmd = cmd->next;
	}
	return (false);
}
