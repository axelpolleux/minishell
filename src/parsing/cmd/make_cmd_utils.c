/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:44:26 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/14 11:33:53 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->input = -1;
	new->output = -1;
	return (new);
}

void	add_cmd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

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
	new->prev = tmp;
}

char	**tokens_to_argv(t_token *start, t_token *end, int i)
{
	char	**argv;

	argv = ft_calloc(sizeof(char *), count_words(start, end) + 1);
	if (!argv)
		return (NULL);
	while (start && start != end)
	{
		if (start->type == WORD)
		{
			if (!start->prev || !is_redir(start->prev->type))
			{
				argv[i] = ft_strdup(start->cmd);
				if (!argv[i])
				{
					free_arr(argv);
					return (NULL);
				}
				i++;
			}
		}
		start = start->next;
	}
	return (argv);
}
