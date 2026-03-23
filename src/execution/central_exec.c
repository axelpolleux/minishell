/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:48:19 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/23 13:28:51 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env, char *motif, t_data *data)
{
	char	**path;
	int		i;
	int		j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], motif, j) && motif[j] == '\0')
		{
			if (env[i][j + 1] == '\0')
			{
				data->path_void = 1;
				return (NULL);
			}
			path = ft_split(env[i] + j + 1, ':');
			if (!path)
				data_malloc_error(data);
			return (path);
		}
	}
	data->path_null = 1;
	return (NULL);
}

int	verif_file(char *file, int in, int doc)
{
	int	fd;

	if (in)
	{
		if (doc)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (!in)
		fd = open(file, O_RDONLY);
	return (fd);
}

void	cmd_whith_path(t_data *data, char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		data->path_and_cmd = command;
	else
		data->path_invalid = 1;
	return ;
}

void	verif_command(t_data *data, char **env)
{
	char	*command;

	command = data->token->cmd_part[0];
	if (srch_cmd(data->token->cmd_part[0], '/'))
	{
		cmd_whith_path(data, command);
		return ;
	}
	else
		data->path = get_path(env, "PATH", data);
	if (!data->path_null && !data->path_void)
		full_cmd(data, command, -1);
}

void	get_cmd_path(char *cmd, char **env, t_data *data)
{
	if (!cmd || !*cmd)
	{
		data->cmd_null = 1;
		return ;
	}
	data->token->cmd_part = ft_split(cmd, ' ');
	if (!data->token->cmd_part)
		data_malloc_error(data);
	if (!data->token->cmd_part[0])
	{
		free(data->token->cmd_part);
		data->token->cmd_part = NULL;
		data->cmd_invalid = 1;
		data->cmd_space_void = cmd;
		return ;
	}
	verif_command(data, env);
}
