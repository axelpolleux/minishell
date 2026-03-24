/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:02:59 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/24 12:04:17 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_st_env    *last_node(t_st_env *nod)
{
	while (nod && nod->next)
		nod = nod->next;
	return (nod);
}

void	add_to_bottom(t_st_env **node, t_st_env *new_bot)
{
	t_st_env	*end;
	if (!new_bot)
		return ;
	if (!*node)
	{
		*node = new_bot;
		return ;
	}
	end = last_node(*node);
	end->next = new_bot;
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
	data->ac = ac;
	data->cmd_n = 0;
	data->st_env = NULL;
	data->token = NULL;
	(void)av;
	return (data);
}
