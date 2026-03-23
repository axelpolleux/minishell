/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:02:59 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/23 14:32:54 by ethutin-         ###   ########.fr       */
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