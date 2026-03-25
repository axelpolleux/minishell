/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:02:59 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/25 10:49:31 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env    *last_node(t_env *nod)
{
	while (nod && nod->next)
		nod = nod->next;
	return (nod);
}

void	add_to_bottom(t_env **node, t_env *new_bot)
{
	t_env	*end;

	if (!new_bot)
		return ;
	if (!*node)
	{
		*node = new_bot;
		return ;
	}
	end = *node;//
	while (end->next)
		end = end->next;
	end->next = new_bot;
	new_bot->prev = end;
	//end = last_node(*node);
	// end->next = new_bot;
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		data_malloc_error(data);
	data->fd_storage[0] = -1;
	data->fd_storage[1] = -1;
	data->last_fd = -1;
	data->env = NULL;
	data->token = NULL;
	(void)av;
	(void)ac;
	return (data);
}
