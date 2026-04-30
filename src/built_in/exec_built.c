/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:53:34 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/30 11:30:33 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	built_parent(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("export", cmd->cmd[0], 6))
		data->exit = exec_export(data, cmd->cmd);
	else if (!ft_strncmp("unset", cmd->cmd[0], 5))
		data->exit = exec_unset(data, cmd->cmd);
	else if (!ft_strncmp("cd", cmd->cmd[0], 2))
		data->exit = exec_cd(data, cmd->cmd);
}

void	built_choice(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd[0], 4))
		data->exit = exec_echo(cmd->cmd);
	else if (!ft_strncmp("pwd", cmd->cmd[0], 3))
		data->exit = exec_pwd();
	else if (!ft_strncmp("env", cmd->cmd[0], 3))
		data->exit = exec_env(data);
	else if (!ft_strncmp("exit", cmd->cmd[0], 4))
		exec_exit(data, cmd, cmd->cmd);
	built_parent(data, cmd);
}

int	exec_built(t_data *data, t_cmd *cmd)
{
	//get_expand(data, cmd);
	if (cmd->output >= 0)
	{
		data->last_fd = dup(1);
		dup2(cmd->output, 1);
	}
	built_choice(data, cmd);
	if (cmd->output >= 0)
	{
		dup2(data->last_fd, 1);
		close (data->last_fd);
	}
	return (data->exit);
}

/*





















































int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin_parent(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd[0], 5))
		return (exec_echo(cmd->cmd));
	else if (!ft_strncmp("pwd", cmd->cmd[0], 4))
		return (exec_pwd());
	else if (!ft_strncmp("env", cmd->cmd[0], 4))
		return (exec_env(data));
	else if (!ft_strncmp("export", cmd->cmd[0], 7))
		return (exec_export(data, cmd->cmd));
	else if (!ft_strncmp("unset", cmd->cmd[0], 6))
		return (exec_unset(data, cmd->cmd));
	else if (!ft_strncmp("cd", cmd->cmd[0], 3))
		return (exec_cd(data, cmd->cmd));
	else if (!ft_strncmp("exit", cmd->cmd[0], 5))
		exec_exit(data, cmd, cmd->cmd);
	return (0);
}

void	exec_builtin_child(t_data *data, t_cmd *cmd)
{
	int	exit_code;

	exit_code = exec_builtin_parent(data, cmd);
	exit(exit_code);
}

int	exec_built(t_data *data, t_cmd *cmd, int has_pipe)
{
	pid_t	pid;

	// 🔴 CAS 1 : PAS de pipe → exec dans parent
	if (!has_pipe)
	{
		if (cmd->output >= 0)
		{
			data->last_fd = dup(1);
			dup2(cmd->output, 1);
		}

		data->exit = exec_builtin_parent(data, cmd);

		if (cmd->output >= 0)
		{
			dup2(data->last_fd, 1);
			close(data->last_fd);
		}
		return (data->exit);
	}

	// 🔴 CAS 2 : PIPE → fork obligatoire
	pid = fork();
	if (pid == 0)
	{
		// redirections
		if (cmd->output >= 0)
			dup2(cmd->output, 1);

		exec_builtin_child(data, cmd);
	}
	else
		waitpid(pid, &data->exit, 0);

	return (WEXITSTATUS(data->exit));
}




*/




