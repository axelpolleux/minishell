/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:48:19 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/30 15:06:39 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_data *data, int i)
{
	t_env 	*tmp;
	char	**path;

	tmp = data->t_env;
	while (tmp)
	{
		i = 0;
		while (tmp->var[i] && tmp->var[i] != '=')
			i++;
		if (!ft_strncmp(tmp->var[i], "PATH", i) && "PATH"[i] == '\0')
		{
			if (tmp->var[i + 1] == '\0')
			{
				data->path_void = 1;
				return (NULL);
			}
			path = ft_split(tmp->var[i]+ 1, ':');
			if (!path)
				data_malloc_error(data);
			return (path);
		}
		tmp = tmp->next;
	}
	data->path_null = 1;
	return (NULL);
}

int		full_void(char *line)
{
	int i;
	
	i = -1;
	if (line)
	{
		while (line[++i])
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
				return (0);
	}
	return (1);
}


int	verif_file(char *file, int doc)
{
	int	fd;

	if (doc == HEREDOC || doc == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (doc == RED_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (doc == RED_IN)
		fd = open(file, O_RDONLY);
	return (fd);
}

void	cmd_whith_path(t_data *data, char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		data->cmd->cmd_path = command;
	else
		data->path_invalid = 1;
	return ;
}

void	verif_command(t_data *data)
{

	t_cmd *tmp;

	tmp = data->cmd;
	if (srch_cmd(tmp->cmd[0], '/'))
	{
		cmd_whith_path(data, tmp->cmd[0]);
		return ;
	}
	else
		data->path = get_path(data, 0);
	if (!data->path_null && !data->path_void)
		full_cmd(data, tmp->cmd[0]);
}

void	get_cmd_path(t_data *data)
{
	t_cmd *tmp;

	tmp = data->cmd;
	if (!tmp->full_cmd || !*tmp->full_cmd)
	{
		data->cmd_null = 1;
		return ;
	}
	if (full_void(tmp->cmd))
		return ;

	verif_command(data);
}
