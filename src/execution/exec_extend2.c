/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:40:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/08 17:06:02 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	nb_process(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	int		count;

// 	count = 0;
// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		if (tmp->type == CMD)
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

bool fcext(t_data *data, t_cmd *cmd, char *path, char *command)
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
	if (cmd->next)
		close(data->fd_storage[0]);
	if (cmd->input != -1)
	{
		if (dup2(cmd->input, STDIN_FILENO) == -1)
			dup_error(data);
		close(cmd->input);
	}
	if (cmd->output != -1)
	{
		if (dup2(cmd->output, STDOUT_FILENO) == -1)
			dup_error(data);
		close(cmd->output);
	}
}

int	verif_file(char *file, int doc)
{
	int	fd;

	fd = -1;
	if (doc == HEREDOC || doc == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (doc == RED_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (doc == RED_IN)
		fd = open(file, O_RDONLY);
	return (fd);
}
