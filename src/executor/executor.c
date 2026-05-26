/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junie <junie@jetbrains.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:40:00 by junie             */
/*   Updated: 2026/05/26 12:40:00 by junie             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	children(t_data *data, t_cmd *cmd)
{
	char	**env;
	int		exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->next)
		dup2(data->fd_storage[1], 1);
	if (cmd->prev)
		dup2(data->last_fd, 0);
	closes(-1, data->fd_storage);
	if (cmd->prev)
		close(data->last_fd);
	if (!check_cmd(data, cmd))
	{
		exit_status = data->exit;
		free_data(data);
		exit(exit_status);
	}
	env = tab_env(data->t_env, -1);
	exec_command(data, cmd, env);
}

void	parent(t_data *data, t_cmd *cmd)
{
	if (cmd->prev)
		close(data->last_fd);
	if (cmd->next)
	{
		data->last_fd = data->fd_storage[0];
		close(data->fd_storage[1]);
	}
}

void	manage_process(t_data *data, t_cmd *cmd)
{
	if (cmd->next)
	{
		if (pipe(data->fd_storage) == -1)
			pipe_error(data);
	}
	data->pid[data->pipe] = fork();
	if (data->pid[data->pipe] == -1)
		fork_error(data);
	if (data->pid[data->pipe] == 0)
		children(data, cmd);
	else
		parent(data, cmd);
}

void	wait_end(t_data *data, int count)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count)
	{
		if (waitpid(data->pid[i], &status, 0) == -1)
			wait_error(data);
		if (WIFEXITED(status))
			data->exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit = 128 + WTERMSIG(status);
	}
}

static void	handle_exec_loop(t_data *data, int count)
{
	t_cmd	*curr;

	curr = data->cmd;
	data->pipe = 0;
	while (curr)
	{
		get_expand(data, curr);
		manage_process(data, curr);
		curr = curr->next;
		data->pipe++;
	}
	wait_end(data, count);
}

void	exec(t_data *data)
{
	t_cmd	*curr;

	if (!data->cmd)
		return ;
	if (heredoc_manage(data, data->cmd))
		return ;
	curr = data->cmd;
	while (curr)
	{
		manage_redir(data, curr);
		curr = curr->next;
	}
	if (!data->cmd->next && is_builtin(data->built_in, data->cmd->command))
	{
		get_expand(data, data->cmd);
		exec_built(data, data->cmd);
		return ;
	}
	data->pid = ft_calloc(sizeof(pid_t), ft_lstsize_c(data->cmd));
	if (!data->pid)
		data_malloc_error(data);
	handle_exec_loop(data, ft_lstsize_c(data->cmd));
}
