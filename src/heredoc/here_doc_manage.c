/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:15 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/01 16:12:10 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	new_delimiter(t_data *data, t_redir_her *doc)
{
	char	*n_line;
	int		i;

	n_line = define_line(data, &i);
	if (!n_line)
		return (true);
	while (doc->file[i])
	{
		if (quote_expand(data, doc->file, &i))
			continue ;
		if (doc->file[i] == '$' && data->quote == NQUOT)
		{
			n_line = get_dollar(data, doc->file, &i, n_line);
			if (!n_line)
				return (true);
			continue ;
		}
		n_line = ft_charjoin(n_line, doc->file[i]);
		if (!n_line)
			return (true);
		i++;
	}
	free(doc->file);
	doc->file = n_line;
	return (false);
}

bool	read_heredoc(t_data *data, t_redir_her *doc, char *tmp, int *fd)
{
	char	*line;

	while (1)
	{
		g_signal = 0;
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			if (line)
				free(line);
			return (true);
		}
		if (!line)
		{
			heredoc_eof_error(doc, fd);
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

void	heredoc_child(t_data *data, t_redir_her *doc, char *tmp, int *fd)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = rl_event;
	close(fd[0]);
	if (new_delimiter(data, doc))
	{
		free(tmp);
		free_data(data);
		exit(1);
	}
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
	int		status;
	char	*tmp;

	tmp = ft_strdup(doc->file);
	if (!tmp)
		return (-2);
	if (pipe(fd) == -1)
		return (free(tmp), -1);
	pid = fork();
	if (pid == -1)
	{
		free(tmp);
		closes(-1, fd);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		heredoc_child(data, doc, tmp, fd);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signal);
	free(tmp);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			data->exit = 130;
			close(fd[0]);
			return (-2);
		}
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		data->exit = 130;
		close(fd[0]);
		return (-2);
	}
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
