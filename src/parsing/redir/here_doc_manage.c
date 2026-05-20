/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:15 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/20 16:22:48 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	read_heredoc(t_data *data, t_redir_her *doc, char *tmp, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		line = expand_here_doc(data, doc, line, tmp);
		if (!line)
		{
			closes(-1, fd);
			return (true);
		}
		if (line && *line && !full_void(line))
			add_history(line);
		if (write_here(doc, line, fd))
			break ;
	}
	return (false);
}

int	init_heredoc(t_data *data, t_redir_her *doc)
{
	char	*tmp;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	tmp = ft_strdup(doc->file);
	if (!tmp)
	{
		closes(-1, fd);
		return (-2);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	if (read_heredoc(data, doc, tmp, fd))
	{
		free(tmp);
		return (-2);
	}
	rl_clear_history();
	free(tmp);
	close(fd[1]);
	return (fd[0]);
}

bool	heredoc_manage(t_data *data, t_cmd *cmd)
{
	t_redir_her	*doc;

	while (cmd)
	{
		doc = cmd->redir;
		while (doc)
		{
			if (doc->type == HEREDOC)
			{
				doc->fd = init_heredoc(data, doc);
				if (doc->fd == -2)
					return (EXIT_FAILURE);
				cmd->input = doc->fd;
			}
			doc = doc->next;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
