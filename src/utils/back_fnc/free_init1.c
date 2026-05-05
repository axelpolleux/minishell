/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:17:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 17:46:59 by ethutin-         ###   ########.fr       */
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
		if (node->var)
			free(node->var);
		if (node->arg)
			free(node->arg);
		if (node->key)
			free(node->key);
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
		tmp = node->next;
		if (node->cmd)
			free_arr(node->cmd);
		if (node->cmd_path)
			free(node->cmd_path);
		if (node->full_cmd)
			free(node->full_cmd);
		free(node);
		node = tmp;
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->path)
			free_arr(data->path);
		if (data->built_env)
			free_arr(data->built_env);
		if (data->built_in)
			free(data->built_in);
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
	rl_clear_history();
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
	data->quote = NQUOT;
	(void)av;
	(void)ac;
	return (data);
}
