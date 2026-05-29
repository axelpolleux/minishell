/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junie <junie@jetbrains.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:00 by junie             */
/*   Updated: 2026/05/26 12:35:00 by junie             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_data *data, t_cmd *cmd, char **env)
{
	int	exit_status;

	apply_redir(data, cmd);
	if (is_builtin(data->built_in, cmd->command))
	{
		built_child(data, cmd);
		exit_status = data->exit;
		free_data(data);
		free_arr(env);
		exit(exit_status);
	}
	if (cmd->cmd_path)
	{
		execve(cmd->cmd_path, cmd->args, env);
		perror("minishell: execve");
	}
	exit_status = data->exit;
	free_data(data);
	free_arr(env);
	exit(exit_status);
}

void	get_path(t_data *data)
{
	char	*path_env;

	path_env = get_arg_env(data, "PATH");
	if (data->path)
		free_arr(data->path);
	if (path_env)
		data->path = ft_split(path_env, ':');
	else
		data->path = NULL;
}

static char	*find_cmd_in_path(t_data *data, char *cmd)
{
	char	*tmp;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') || !data->path)
		return (NULL);
	i = -1;
	while (data->path[++i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}

int	check_cmd(t_data *data, t_cmd *cmd, int *status)
{
	if (!cmd || !cmd->command || !cmd->command[0])
		return (EXIT_FAILURE);
	if (is_builtin(data->built_in, cmd->command))
		return (1);
	get_path(data);
	cmd->cmd_path = find_cmd_in_path(data, cmd->command);
	if (!cmd->cmd_path)
	{
		*(status) = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->command, 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit = 127;
		return (0);
	}
	return (1);
}

void	wait_end(t_data *data, int count)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count)
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(data->pid[i], &status, 0) == -1)
			wait_error(data);
		signal(SIGINT, handle_signal);
		if (WIFEXITED(status))
			data->exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit = 128 + WTERMSIG(status);
	}
	free(data->pid);
	data->pid = NULL;
}
