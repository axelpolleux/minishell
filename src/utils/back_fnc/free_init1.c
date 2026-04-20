/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:17:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/20 10:07:40 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *node)
{
	t_token	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
		if (node->cmd)
			free(node->cmd);
		free(node);
		node = tmp;
	}
	node = NULL;
}

void	free_env(t_env *node)
{
	t_env	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
		free(node->var);
		free(node);
		node = tmp;
	}
	node = NULL;
}

void	free_cmd(t_cmd *node)
{
	t_cmd	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
		if (tmp->cmd)
			free_arr(tmp->cmd);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->full_cmd)
			free(tmp->full_cmd);
		free(node);
		node = tmp;
	}
	node = NULL;
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->path)
			free_arr(data->path);
		if (data->built_in)
			free_arr(data->built_in);
		if (data->built_env)
			free_arr(data->built_env);
		if (data->pid)
			free(data->pid);
		if (data->line)
			free(data->line);
		if (data->token)
			free_token(data->token);
		if (data->t_env)
			free_env(data->t_env);
		if (data->cmd)
			free_cmd(data->cmd);
		free(data);
	}
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		data_malloc_error(data);
	data->fd_storage[0] = -1;
	data->fd_storage[1] = -1;
	data->t_env = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->exit = -2;
	(void)av;
	(void)ac;
	return (data);
}
