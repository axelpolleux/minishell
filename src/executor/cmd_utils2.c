/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:38:06 by apolleux          #+#    #+#             */
/*   Updated: 2026/06/02 13:49:16 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_command(t_data *data, t_cmd *cmd, char **env)
{
	int	exit_status;

	apply_redir(data, cmd);
	if (cmd->executable)
	{
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
	}
	exit_status = data->exit;
	free_data(data);
	free_arr(env);
	exit(exit_status);
}
