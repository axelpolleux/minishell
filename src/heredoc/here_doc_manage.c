/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:15 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/29 17:37:12 by ethutin-         ###   ########.fr       */
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
	printf("old_delim: %s\n", doc->file);
	while (doc->file[i])
	{
		// checker le new et le old delim
		if (quote_expand(data, doc->file, &i))
			continue ;
		n_line = ft_charjoin(n_line, doc->file[i]);
		if (!n_line)
			return (true);
		i++;
	}
		printf("new_delim: %s\n", doc->file);

	free(doc->file);
	doc->file = n_line;
	if (!doc->file)
		return (true);
	return (false);
}

// bool	read_heredoc(t_data *data, t_redir_her *doc, char *tmp, int *fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			if (g_signal == SIGINT)
// 			{
// 				closes(-1, fd);
// 				data->exit = 130;
// 				return (true);
// 			}
// 			close(fd[1]);
// 			break ;
// 		}
// 		if (history_heredoc(data, line, fd))
// 			return (true);
// 		line = expand_here_doc(data, doc, line, tmp);
// 		if (!line)
// 		{
// 			closes(-1, fd);
// 			return (true);
// 		}
// 		if (write_here(doc, line, fd))
// 			break ;
// 	}
// 	return (false);
// }

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

void	heredoc_child(t_data *data, t_redir_her *doc, char *tmp, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	if (new_delimiter(data, doc))
		exit(1);
	if (read_heredoc(data, doc, tmp, fd))
		exit(1);
	close(fd[1]);
	free_data(data);
	exit(0);
}

// int	init_heredoc(t_data *data, t_redir_her *doc)
// {
// 	char	*tmp;
// 	int		fd[2];

// 	g_signal = 0;
// 	tmp = ft_strdup(doc->file);
// 	if (!tmp)
// 		return (-2);
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, handle_heredoc);
// 	if (new_delimiter(data, doc))
// 	{
// 		free(tmp);
// 		return (-2);
// 	}
// 	if (read_heredoc(data, doc, tmp, fd))
// 	{
// 		free(tmp);
// 		signal(SIGINT, handle_signal);
// 		signal(SIGQUIT, SIG_IGN);
// 		return (-2);
// 	}
// 	signal(SIGINT, handle_signal);
// 	signal(SIGQUIT, SIG_IGN);
// 	free(tmp);
// 	close(fd[1]);
// 	return (fd[0]);
// }


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
		return (-1);
	}
	if (pid == 0)
		heredoc_child(data, doc, tmp, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
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
			}
			doc = doc->next;
		}
		cmd = cmd->next;
	}
	return (false);
}
