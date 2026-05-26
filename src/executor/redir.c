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

static void	handle_in(t_data *data, t_cmd *cmd, t_redir_her *curr)
{
	if (cmd->input > -1)
		close(cmd->input);
	if (curr->type == RED_IN)
		cmd->input = open(curr->file, O_RDONLY);
	else
		cmd->input = curr->fd;
	if (cmd->input == -1)
		open_error(data);
}

static void	handle_out(t_data *data, t_cmd *cmd, t_redir_her *curr)
{
	if (cmd->output > -1)
		close(cmd->output);
	if (curr->type == RED_OUT)
		cmd->output = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->output = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->output == -1)
		open_error(data);
}

void	manage_redir(t_data *data, t_cmd *cmd)
{
	t_redir_her	*curr;

	curr = cmd->redir;
	while (curr)
	{
		if (curr->type == RED_IN || curr->type == HEREDOC)
			handle_in(data, cmd, curr);
		else if (curr->type == RED_OUT || curr->type == APPEND)
			handle_out(data, cmd, curr);
		curr = curr->next;
	}
}

void	apply_redir(t_cmd *cmd)
{
	if (cmd->input > -1)
	{
		dup2(cmd->input, 0);
		close(cmd->input);
	}
	if (cmd->output > -1)
	{
		dup2(cmd->output, 1);
		close(cmd->output);
	}
}
