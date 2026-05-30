/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junie <junie@jetbrains.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:30:00 by junie             */
/*   Updated: 2026/05/26 12:30:00 by junie             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_in(t_cmd *cmd, t_redir_her *curr)
{
    if (curr->type == RED_IN)
    {
        if (cmd->input > -1)
            close(cmd->input);
        cmd->input = open(curr->file, O_RDONLY);
    }
    else
    {
        if (cmd->input > -1 && cmd->input != curr->fd)
            close(cmd->input);
        cmd->input = curr->fd;
    }
    if (cmd->input == -1)
        return (0);
    return (1);
}

int	handle_out(t_cmd *cmd, t_redir_her *curr)
{
	if (cmd->output > -1)
		close(cmd->output);
	if (curr->type == RED_OUT)
		cmd->output = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->output = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->output == -1)
		return (0);
	return (1);
}

int	manage_redir(t_data *data, t_cmd *cmd)
{
	int			state;
	t_redir_her	*curr;

	state = 1;
	curr = cmd->redir;
	while (curr)
	{
		if (curr->type == RED_IN || curr->type == HEREDOC)
			state = handle_in(cmd, curr);
		else if (curr->type == RED_OUT || curr->type == APPEND)
			state = handle_out(cmd, curr);
		if (!state)
		{
			display_cmd(cmd);
			// opendir_error(data, cmd->args);
			opendir_error(data, cmd->redir->file);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	apply_redir(t_data *data, t_cmd *cmd)
{
	if (cmd->input > -1)
	{
		if (dup2(cmd->input, 0) == -1)
    		dup_error(data);
		close(cmd->input);
	}
	if (cmd->output > -1)
	{
		if (dup2(cmd->output, 1) == -1)
    		dup_error(data);
		close(cmd->output);
	}
}
