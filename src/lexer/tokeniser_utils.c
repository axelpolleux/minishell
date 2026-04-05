/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:30:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/05 17:35:18 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/lib/minishell.h"

void	display_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		printf("%d: {%s - %d}\n", i, token->cmd, token->type);
		i++;
		token = token->next;
	}
}

void	free_tokens()

t_token	*token_new(char *cmd, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->cmd = cmd;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}