/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:14:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/26 14:16:33 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token *prev, char *cmd)
{
	t_token	*new_node;

	new_node = ft_calloc(sizeof(t_token), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->type = 0;
	new_node->cmd = cmd;
	new_node->next = NULL;
	new_node->prev = prev;
	return (new_node);
}

t_env	*new_env(char *line)
{
	t_env	*new_node;

	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->var = line;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
