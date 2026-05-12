/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:27:15 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/12 17:14:15 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*find_cmd(t_token *tokens)
// {
//
// }

t_cmd	*ft_cmd_new()
{
	t_cmd	*new;

	return (new);
}

t_cmd	*parse_commands(t_token *tokens)
{
	t_cmd	*res;

	res = ft_calloc(1, sizeof(t_cmd *));
	while (tokens->type != WORD)
		tokens = tokens->next;
	res->command = tokens->cmd;
	return (res);
}
