/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:40:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/21 09:48:26 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_process(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == CMD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	full_cmd(t_data *data, char *command)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->path && data->path[++i])
	{
		if (data->path[i][0] == '\0')
			tmp = ft_strdup("./");
		else
			tmp = ft_strjoin(data->path[i], "/");
		if (!tmp)
			data_malloc_error(data);
		data->cmd->cmd_path = ft_strjoin(tmp, command);
		free(tmp);
		if (!data->cmd->cmd_path)
			data_malloc_error(data);
		if (access(data->cmd->cmd_path, F_OK | X_OK) == 0)
			return ;
		else
		{
			perror(command);
			data->exit = 126;
		}
	}
}

char	**get_path(t_data *data, int len)
{
	t_env	*tmp;
	char	**path;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, PATH, len))
		{
			if (tmp->var[len + 1] == '\0')
			{
				data->exit = 127;
				return (NULL);
			}
			path = ft_split(tmp->var + len, ':');
			if (!path)
				data_malloc_error(data);
			return (path);
		}
		tmp = tmp->next;
	}
	data->exit = 127;
	return (NULL);
}

// void	tennage(t_data *data)
// {
// 	if (data->cmd->type == RED_OUT || data->cmd->type == APPEND
//         || data->cmd->type == HEREDOC ||  data->cmd->type == RED_IN)
// 	{
// 		data->fd = verif_file(data->cmd->cmd[1], data->cmd->type);
// 		if (data->fd == -1)
// 			open_error(data);
// 		if (dup2(data->fd, 1) == -1)
// 			exit(EXIT_FAILURE);
// 		close(data->fd);
// 	}
// 	else
// 	{
// 		if (dup2(data->fd_storage[1], 1) == -1)
// 			exit(EXIT_FAILURE);
// 		closes(-1, data->fd_storage);
// 	}
// }