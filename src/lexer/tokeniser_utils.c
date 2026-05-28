/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:30:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/27 16:16:33 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

t_token	*token_new(char *input, int len, int type, bool quot)
{
	t_token	*new;
	char	*cmd;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	cmd = ft_substr(input, 0, len);
	if (!cmd)
	{
		free(new);
		return (NULL);
	}
	new->cmd = cmd;
	new->type = type;
	new->quot = quot;
	new->next = NULL;
	return (new);
}
