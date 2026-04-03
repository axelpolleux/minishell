/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:53:34 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/03 14:41:47 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	built_choice(t_data *data, t_cmd *cmd)
// {
// 	if (!ft_strncmp("echo", cmd->cmd[0], 5))
// 		data->exit = exec_echo(cmd->cmd);
// 	else if (!ft_strncmp("cd", cmd->cmd[0], 2))
// 		data->exit = exec_cd(data, cmd->cmd);
// 	else if (!ft_strncmp("pwd", cmd->cmd[0], 3))
// 		data->exit = exec_pwd();
// 	else if (!ft_strncmp("export", cmd->cmd[0], 6))
// 		data->exit = exec_export(data, cmd->cmd);
// 	else if (!ft_strncmp("unset", cmd->cmd[0], 5))
// 		data->exit = exec_unset( data, cmd->cmd);
// 	else if (!ft_strncmp("env", cmd->cmd[0], 3))
// 		data->exit = exec_env(data);
// 	// else if (!ft_strncmp("exit", cmd->cmd[0], 4))
// 	// {
//     // }

// }

// void exec_built(t_data *data, t_cmd *cmd)
// {
// 	if (cmd->output >= 0)
// 	{
// 		data->last_fd = dup(1);
// 		dup2(cmd->output, 1);
// 	}
// 	built_choice(data, cmd);
// 	if (cmd->output >= 0)
// 	{
// 		dup2(data->last_fd, 1);
// 		close (data->last_fd);
// 	}
// }

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/
