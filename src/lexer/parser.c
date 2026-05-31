/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:36:34 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/31 19:33:43 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	while (start && start != end)
	{
		if (start->type == WORD)
			count++;
		else if (is_redir(start->type))
		{
			if (start->next)
				start = start->next;
		}
		start = start->next;
	}
	return (count);
}

char	**tokens_to_argv(t_token *start, t_token *end, int i)
{
	char	**argv;
	int		count;

	count = count_words(start, end);
	argv = ft_calloc(sizeof(char *), count + 1);
	if (!argv)
		return (NULL);
	while (start && start != end)
	{
		if (start->type == WORD)
		{
			argv[i] = ft_strdup(start->cmd);
			if (!argv[i])
			{
				free_arr(argv);
				return (NULL);
			}
			i++;
		}
		else if (is_redir(start->type))
		{
			if (start->next)
				start = start->next;
		}
		start = start->next;
	}
	return (argv);
}

t_redir_her	*new_redir_node(char *file, int type)
{
	t_redir_her	*new;

	new = ft_calloc(sizeof(t_redir_her), 1);
	if (!new)
		return (NULL);
	new->file = ft_strdup(file);
	if (!new->file)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->fd = -1;
	return (new);
}

int	handle_redirs(t_cmd *cmd, t_token *start, t_token *end)
{
	t_redir_her	*new;

	while (start && start != end)
	{
		if (is_redir(start->type))
		{
			if (!start->next || start->next->type != WORD)
				return (EXIT_FAILURE);
			new = new_redir_node(start->next->cmd, start->type);
			if (!new)
				return (EXIT_FAILURE);
			add_redir_back(&cmd->redir, new);
			start = start->next;
		}
		start = start->next;
	}
	return (EXIT_SUCCESS);
}
