/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:40:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/14 17:01:47 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	fcext(t_data *data, t_cmd *cmd, char *path, char *command)
{
	if (access(path, F_OK) == 0)
	{
		if (check_directory(data, cmd->cmd_path))
			return (true);
		if (access(path, X_OK) == 0)
		{
			cmd->cmd_path = path;
			return (true);
		}
		perror(command);
		free(path);
		data->exit = 126;
		return (true);
	}
	return (false);
}

void	manage_redir(t_data *data, t_cmd *cmd)
{
	t_redir_her	*redir;
	int			fd;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
			fd = redir->fd;
		else
			fd = verif_file(redir->file, redir->type);
		if (fd < 0)
		{
			perror(redir->file);
			exit(1);
		}
		if (redir->type == RED_IN || redir->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	if (cmd->next)
		if (dup2(data->fd_storage[1], STDOUT_FILENO) == -1)
			dup_error(data);
	write(1, "ici\n", 4);

}

int	verif_file(char *file, int doc)
{
	int	fd;

	fd = -1;
	if (doc == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (doc == RED_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (doc == RED_IN)
		fd = open(file, O_RDONLY);
	return (fd);
}

void	wait_end(t_data *data, int count)
{
	int	i;
	int	error;

	i = -1;
	while (++i < count)
		if (waitpid(data->pid[i], &error, 0) == -1)
			wait_error(data);
	if (WIFEXITED(error))
		data->exit = (WEXITSTATUS(error));
	free(data->pid);
	data->pid = NULL;
}
