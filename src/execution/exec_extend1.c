/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:48:19 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/11 15:40:25 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	full_cmd(t_data *data, t_cmd *cmd, char *command, int i)
{
	char	*tmp;
	char	*path;

	while (data->path && data->path[++i])
	{
		if (data->path[i][0] == '\0')
			tmp = ft_strdup("./");
		else
			tmp = ft_strjoin(data->path[i], "/");
		if (!tmp)
			data_malloc_error(data);
		path = ft_strjoin_upd(tmp, command);
		if (!path)
			data_malloc_error(data);
		if (fcext(data, cmd, path, command))
			return ;
		free(path);
	}
	error_cnf(data, command);
}

void	get_path(t_data *data)
{
	t_env	*tmp;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, PATH))
		{
			if (!tmp->arg || tmp->var[0] == '\0')
			{
				data->exit = 127;
				return ;
			}
			data->path = ft_split(tmp->arg, ':');
			if (!data->path)
				data_malloc_error(data);
			return ;
		}
		tmp = tmp->next;
	}
	data->exit = 127;
}

void	cmd_with_path(t_data *data, t_cmd *cmd, char *command)
{
	if (access(command, F_OK) != 0)
	{
		perror(command);
		data->exit = 127;
		return ;
	}
	if (!check_directory(data, command))
		return ;
	if (access(command, X_OK) != 0)
	{
		perror(command);
		data->exit = 126;
		return ;
	}
	cmd->cmd_path = ft_strdup(command);
	if (!cmd->cmd_path)
		data_malloc_error(data);
}

int	check_directory(t_data *data, char *path)
{
	struct stat	st;

	if (!path)
		return (false);
	if (stat(path, &st) == -1)
		return (false);
	if (S_ISDIR(st.st_mode))
	{
		opendir_error(data, path);
		return (false);
	}
	return (true);
}

int	check_cmd(t_data *data, t_cmd *cmd)
{
	data->exit = -1;
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (EXIT_FAILURE);
	if (srch_cmd(cmd->cmd[0], '/'))
		cmd_with_path(data, cmd, cmd->cmd[0]);
	else
	{
		get_path(data);
		if (data->exit == -1)
			full_cmd(data, cmd, cmd->cmd[0], -1);
	}
	if (data->exit == 126 || data->exit == 127)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}