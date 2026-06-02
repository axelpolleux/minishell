/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:15 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/02 13:46:01 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_readline(t_redir_her *doc, char **line, int *fd)
{
	g_signal = 0;
	*line = readline("> ");
	if (g_signal == SIGINT)
	{
		if (*line)
			free(*line);
		*line = NULL;
		return (-1);
	}
	if (!*line)
	{
		heredoc_eof_error(doc, fd);
		return (1);
	}
	return (0);
}

bool	read_heredoc(t_data *data, t_redir_her *doc, char *tmp, int *fd)
{
	char	*line;
	int		state;

	while (1)
	{
		state = check_readline(doc, &line, fd);
		if (state == -1)
			return (true);
		if (state == 1)
			break ;
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

void	heredoc_child(t_data *data, t_redir_her *doc, char *tmp, int *fd)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	if (read_heredoc(data, doc, tmp, fd))
	{
		free(tmp);
		close(fd[1]);
		free_data(data);
		if (g_signal == SIGINT)
			exit(130);
		exit(1);
	}
	close(fd[1]);
	free(tmp);
	free_data(data);
	exit(0);
}

int	init_heredoc(t_data *data, t_redir_her *doc)
{
	pid_t	pid;
	int		fd[2];
	char	*tmp;

	tmp = ft_strdup(doc->file);
	if (!tmp)
		return (-2);
	if (pipe(fd) == -1)
	{
		free(tmp);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		free(tmp);
		closes(-1, fd);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		heredoc_child(data, doc, tmp, fd);
	if (wait_heredoc(data, pid, tmp, fd))
		return (-2);
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
			if (expand_redir(data, doc))
				return (true);
			if (doc->type == HEREDOC)
			{
				doc->fd = init_heredoc(data, doc);
				if (doc->fd == -2)
					return (true);
			}
			doc = doc->next;
		}
		cmd = cmd->next;
	}
	return (false);
}
