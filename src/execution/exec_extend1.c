/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:48:19 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/14 15:09:18 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_file(char *file, int doc)
{
	int	fd;

	fd = -1;
	if (doc == HEREDOC || doc == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (doc == RED_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (doc == RED_IN)
		fd = open(file, O_RDONLY);
	return (fd);
}

void	cmd_whith_path(t_data *data, char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		data->cmd->cmd_path = command;
	else
	{
		perror(command);
		data->exit = 126;
	}
}

void	verif_command(t_data *data, t_cmd *cmd)
{
	if (srch_cmd(cmd->cmd[0], '/'))
	{
		cmd_whith_path(data, cmd->cmd[0]);
		return ;
	}
	else
		data->path = get_path(data, ft_strlen(PATH));
	if (data->exit == -1)
		full_cmd(data, cmd->cmd[0]);
}

void	get_cmd_path(t_data *data, t_cmd *cmd)
{
	if (!cmd->full_cmd || !*cmd->full_cmd)
	{
		data->exit = 126;
		return ;
	}
	else if (full_void(cmd->cmd[0]))
	{
		data->exit = 127;
		return ;
	}
	verif_command(data, cmd);
}

void	manage_redir(t_data *data, t_cmd *cmd)
{
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
