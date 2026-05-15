/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:15 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/14 14:50:58 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_heredoc(t_redir_her *doc)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, doc->file))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

void	heredoc_manage(t_cmd *cmd)
{
	t_redir_her	*doc;

	while (cmd)
	{
		doc = cmd->redir;
		while (doc)
		{
			if (doc->type == HEREDOC)
			{
				doc->fd = init_heredoc(doc);
				cmd->input = doc->fd;
			}
			doc = doc->next;
		}
		cmd = cmd->next;
	}
}
