/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:44:12 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/22 15:11:14 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/lib/minishell.h"

t_cmd	*commander(t_token *tokens)
{
	t_cmd	*commands;

	commands = NULL;
	while (tokens)
	{
		tokens = tokens->next;
	}
	return (commands);
}
