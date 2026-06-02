/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:40:15 by apolleux          #+#    #+#             */
/*   Updated: 2026/06/02 13:49:12 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_path_entry(char *dir, char *cmd, char **saved)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(full, X_OK) == 0)
	{
		if (*saved)
			free(*saved);
		return (full);
	}
	if (!*saved && access(full, F_OK) == 0)
		*saved = ft_strdup(full);
	free(full);
	return (NULL);
}

static char	*find_cmd_in_path(t_data *data, char *cmd)
{
	char	*result;
	char	*saved_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!data->path)
		return (NULL);
	i = -1;
	saved_path = NULL;
	while (data->path[++i])
	{
		result = try_path_entry(data->path[i], cmd, &saved_path);
		if (result)
			return (result);
	}
	return (saved_path);
}

static int	report_err(char *cmd, char *msg, int code, int *status)
{
	ft_putstr_fd("minichevre: ", 2);
	if (msg)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(msg, 2);
	}
	else
		perror(cmd);
	*status = code;
	return (code);
}

static int	check_exec(t_data *data, t_cmd *cmd, int *status)
{
	struct stat	s;

	if (stat(cmd->cmd_path, &s) == 0 && S_ISDIR(s.st_mode))
	{
		data->exit = report_err(cmd->command,
				": Is a directory\n", 126, status);
		return (0);
	}
	if (access(cmd->cmd_path, X_OK) != 0)
	{
		data->exit = report_err(cmd->command, NULL, 126, status);
		return (0);
	}
	return (1);
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
		data->exit = report_err(cmd->command,
				": command not found\n", 127, status);
		return (0);
	}
	return (check_exec(data, cmd, status));
}
