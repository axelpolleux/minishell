/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:53:34 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/02 13:56:45 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_parent(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("export", cmd->command, 6))
		data->exit = exec_export(data, cmd->args);
	else if (!ft_strncmp("unset", cmd->command, 5))
		data->exit = exec_unset(data, cmd->args);
	else if (!ft_strncmp("cd", cmd->command, 2))
		data->exit = exec_cd(data, cmd->args);
	else
		built_child(data, cmd);
}

void	built_child(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->command, 4))
		data->exit = exec_echo(cmd->args);
	else if (!ft_strncmp("pwd", cmd->command, 3))
		data->exit = exec_pwd(data);
	else if (!ft_strncmp("env", cmd->command, 3))
		data->exit = exec_env(data);
	else if (!ft_strncmp("exit", cmd->command, 4))
		exec_exit(data, cmd, cmd->args);
}

static void	close_it(int save_in, int save_out, t_cmd *cmd)
{
	if (save_in > -1)
	{
		dup2(save_in, 0);
		close(save_in);
	}
	if (save_out > -1)
	{
		dup2(save_out, 1);
		close(save_out);
	}
	if (cmd->input > -1)
	{
		close(cmd->input);
		cmd->input = -1;
	}
	if (cmd->output > -1)
	{
		close(cmd->output);
		cmd->output = -1;
	}
}

void	exec_built(t_data *data, t_cmd *cmd)
{
	int	save_in;
	int	save_out;

	save_in = -1;
	save_out = -1;
	if (cmd->input > -1)
	{
		save_in = dup(0);
		dup2(cmd->input, 0);
	}
	if (cmd->output > -1)
	{
		save_out = dup(1);
		dup2(cmd->output, 1);
	}
	built_parent(data, cmd);
	fflush(stdout);
	close_it(save_in, save_out, cmd);
}
