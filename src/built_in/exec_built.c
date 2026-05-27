/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:53:34 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/26 16:38:10 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_parent(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("export", cmd->args[0], 6))
		data->exit = exec_export(data, cmd->args);
	else if (!ft_strncmp("unset", cmd->args[0], 5))
		data->exit = exec_unset(data, cmd->args);
	else if (!ft_strncmp("cd", cmd->args[0], 2))
		data->exit = exec_cd(data, cmd->args);
	built_child(data, cmd);
}

void	built_child(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->args[0], 4))
		data->exit = exec_echo(cmd->args);
	else if (!ft_strncmp("pwd", cmd->args[0], 3))
		data->exit = exec_pwd();
	else if (!ft_strncmp("env", cmd->args[0], 3))
		data->exit = exec_env(data);
	else if (!ft_strncmp("exit", cmd->args[0], 4))
		exec_exit(data, cmd, cmd->args);
}

void	exec_built(t_data *data, t_cmd *cmd)
{
	if (cmd->output > -1)
	{
		data->last_fd = dup(1);
		dup2(cmd->output, 1);
	}
	built_parent(data, cmd);
	if (cmd->output > -1)
	{
		dup2(data->last_fd, 1);
		close (data->last_fd);
	}
}
