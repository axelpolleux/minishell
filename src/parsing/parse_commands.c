/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:27:15 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/13 18:35:15 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*find_cmd(t_token *tokens)
// {
//
// }

t_cmd	*ft_cmd_new(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (0);
	return (new);
}

t_cmd	*parse_commands(t_token *tokens)
{
	t_cmd	*res;

	res = ft_cmd_new();
	while (tokens->type != WORD)
		tokens = tokens->next;
	res->command = ft_strdup(tokens->cmd);
	if (!res->command)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
