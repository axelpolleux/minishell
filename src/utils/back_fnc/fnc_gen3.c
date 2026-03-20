/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:42:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/20 18:19:46 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include"exec.h"

t_node	*newnode(int i, int type, char ** split_cmd)
{
	t_node	*new_node;

	new_node = ft_calloc(sizeof(t_node), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->type =  type;
	new_node->pos = i;
    new_node->cmd_part = split_cmd;
    if (split_cmd)
        new_node->cmd = split_cmd[0];
    new_node->next = NULL;
	return (new_node);
}

t_node	*last_node(t_node *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

int	ft_lstsize(t_node *lst)
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

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->path)
			free_arr(data->path);
		if (data->pid)
			free(data->pid);
		free(data);
	}
}

void	free_stack(t_node *node)
{
	t_node	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
        free_arr(node->cmd_part);
		free(node);
		node = tmp;
	}
	node = NULL;
}