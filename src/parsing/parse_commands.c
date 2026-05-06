/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:10:40 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/06 15:42:47 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
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

char	**tokens_to_argv(t_token *start, t_token *end)
{
	char	**argv;
	int		i;

	argv = ft_calloc(count_words(start, end) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (start && start != end)
	{
		if (start->type != PIPE)
		{
			argv[i] = ft_strdup(start->cmd);
			if (!argv[i])
				return (free_arr(argv));
			i++;
		}
		start = start->next;
	}
	return (argv);
}

t_cmd	*parse_commands(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*new;
	t_token	*start;

	cmds = NULL;
	start = tokens;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			new = new_cmd_node();
			if (!new)
				return (free_cmd(cmds), NULL);
			new->cmd = tokens_to_argv(start, tokens);
			add_cmd_back(&cmds, new);
			start = tokens->next;
		}
		tokens = tokens->next;
	}
	if (start)
	{
		new = new_cmd_node();
		if (!new)
			return (free_cmd(cmds), NULL);
		new->cmd = tokens_to_argv(start, NULL);
		add_cmd_back(&cmds, new);
	}
	return (cmds);
}
