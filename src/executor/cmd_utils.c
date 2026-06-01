/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:40:15 by apolleux          #+#    #+#             */
/*   Updated: 2026/06/02 01:02:23 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*find_cmd_in_path(t_data *data, char *cmd, int i)
{
	struct stat	s;
	char		*tmp;
	char		*full;
	char		*saved_path;

	if (ft_strchr(cmd, '/'))
	{
		tmp = ft_strdup(cmd);
		return (tmp);
	}
	if (!data->path)
		return (NULL);
	saved_path = NULL;
	while (data->path[++i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(full, &s) == 0 && !S_ISDIR(s.st_mode))
		{
			if (access(full, X_OK) == 0)
			{
				if (saved_path)
					free(saved_path);
				return (full);
			}
			if (!saved_path)
			{
				saved_path = ft_strdup(full);
				if (!saved_path)
					data->exit = -2;
				free(full);
				return (saved_path);
			}
		}
		free(full);
	}
	return (saved_path);
}

static int	report_err(t_data *data, char *cmd, int code, int *status) //terminer la norme
{
	if (data->exit == -2)
	{
		
	}
	ft_putstr_fd("minichevre: ", 2);
	if (data->exit == -2)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(CMD_NF, 2);
	}
	else
		perror(cmd);
	*status = code;
	data->exit = code;
	return (0);
}

int	check_cmd(t_data *data, t_cmd *cmd, int *status)
{
	struct stat	s;

	if (!cmd || !cmd->command)
		return (EXIT_FAILURE);
	if (is_builtin(data->built_in, cmd->command))
		return (1);
	get_path(data);
	cmd->cmd_path = find_cmd_in_path(data, cmd->command, -1);
	if (!cmd->cmd_path)
	{
		return (report_err(data, cmd->command, 127, status));
		// data->exit = report_err(cmd->command, CMD_NF, 127, status);
		// return (0);
	}
	if (stat(cmd->cmd_path, &s) == 0 && S_ISDIR(s.st_mode))
	{
		data->exit = report_err(data, cmd->command, 126, status); // NOT_DR
		return (0);
	}
	if (access(cmd->cmd_path, X_OK) != 0)
	{
		data->exit = report_err(data, cmd->command, 126, status); //NULL
		return (0);
	}
	return (1);
}
