/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:01:10 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/29 14:03:01 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir_back(t_redir_her **lst, t_redir_her *new)
{
	t_redir_her	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_redir(int type)
{
	if (type == RED_IN || type == RED_OUT
		|| type == APPEND || type == HEREDOC)
		return (true);
	return (false);
}

int	count_words(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	while (start && start != end)
	{
		if (start->type == WORD)
			if (!start->prev || !is_redir(start->prev->type))
				count++;
		start = start->next;
	}
	return (count);
}

