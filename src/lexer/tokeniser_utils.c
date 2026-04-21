/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:30:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/20 18:39:13 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=============choisiser celui que vou voulait==========//
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

void	display_token(t_token *view)
{
	printf("{");
	while (view)
	{
		printf("%s:%d", view->cmd, view->type);
		if (view->next)
			printf(", ");
		view = view->next;
	}
	printf("}\n");
}
//=========================================================//

int	is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

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

t_token	*token_new(char *input, int *index, int len, int type)
{
	t_token	*new;
	char	*cmd;

	if (!input || !index || *index < 0 || len < 0)
		return (NULL);
	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	cmd = ft_substr(input, *index, len);
	if (!cmd)
		return (NULL);
	new->cmd = cmd;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
