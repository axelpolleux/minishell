/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:42:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/23 15:19:26 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*newnode(int i, int type, char **split_cmd)
{
	t_token	*new_node;

	new_node = ft_calloc(sizeof(t_token), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->pos = i;
	new_node->cmd_part = split_cmd;
	if (split_cmd)
		new_node->cmd = split_cmd[0];
	new_node->next = NULL;
	return (new_node);
}

t_st_env	*new_env(char *line)
{
	t_st_env	*new_node;

	new_node = ft_calloc(sizeof(t_st_env), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->var = line;
	new_node->next = NULL;
	return (new_node);
}

int	ft_lstsize(t_token *lst)
{
	size_t	len_lst;

	len_lst = 0;
	while (lst)
	{
		len_lst++;
		lst = lst->next;
	}
	return (len_lst);
}

void	free_token(t_token *node)
{
	t_token	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
		if (node->cmd_part)
			free_arr(node->cmd_part);
		free(node);
		node = tmp;
	}
	node = NULL;
}

void	free_env(t_st_env *node)
{
	t_st_env	*tmp;

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

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->path)
			free_arr(data->path);
		if (data->env)
			free_arr(data->env);
		if (data->pid)
			free(data->pid);
		if (data->token)
			free_token(data->token);
		if (data->st_env)
			free_env(data->st_env);
		free(data);
	}
}
