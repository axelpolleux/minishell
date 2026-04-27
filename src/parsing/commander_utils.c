/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:42:55 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/27 17:32:54 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_word(t_cmd command, char *word)


t_cmd	*command_new()
{
	t_cmd	*new;

	if (!token)
		return (0);
	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (0);
	return (new);
}