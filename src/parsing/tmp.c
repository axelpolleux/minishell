/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:01:14 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/07 17:15:36 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tmp.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/05/07 16:01:14 by apolleux          #+#    #+#             */
// /*   Updated: 2026/05/07 16:01:28 by apolleux         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
//
// #include "minishell.h"
//
// int	count_words(t_token **start, t_token *end)
// {
// 	int		count;
// 	t_token	*tmp;
//
// 	count = 0;
// 	tmp = *start;
// 	while (tmp && tmp != end)
// 	{
// 		if (tmp->type != PIPE)
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }
//
// t_cmd	*new_cmd_node(void)
// {
// 	t_cmd	*new;
//
// 	new = ft_calloc(1, sizeof(t_cmd));
// 	if (!new)
// 		return (NULL);
// 	new->input = -1;
// 	new->output = -1;
// 	return (new);
// }
//
// void	add_cmd_back(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd	*tmp;
//
// 	if (!lst || !new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	tmp = *lst;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// 	new->prev = tmp;
// }
//
// char	**tokens_to_argv(t_token **start, t_token *end)
// {
// 	t_token	*tmp;
// 	char	**argv;
// 	int		i;
//
// 	tmp = *start;
// 	argv = ft_calloc(count_words(&tmp, end) + 1, sizeof(char *));
// 	if (!argv)
// 		return (NULL);
// 	i = 0;
// 	while (tmp && tmp != end)
// 	{
// 		if (tmp->type != PIPE)
// 		{
// 			argv[i] = ft_strdup(tmp->cmd);
// 			if (!argv[i])
// 				return (free_arr(argv));
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (argv);
// }
//
// t_cmd	*parse_commands(t_token *tokens)
// {
// 	t_cmd	*cmds;
// 	t_cmd	*new;
// 	t_token	*start;
//
// 	cmds = NULL;
// 	start = tokens;
// 	while (tokens)
// 	{
// 		if (tokens->type == PIPE)
// 		{
// 			new = new_cmd_node();
// 			if (!new)
// 				return (free_cmd(cmds), NULL);
// 			new->cmd = tokens_to_argv(&start, tokens);
// 			if (!new->cmd)
// 			{
// 				free(new);
// 				free_cmd(cmds);
// 				return (NULL);
// 			}
// 			add_cmd_back(&cmds, new);
// 			start = tokens->next;
// 		}
// 		tokens = tokens->next;
// 	}
// 	if (start)
// 	{
// 		new = new_cmd_node();
// 		if (!new)
// 			return (free_cmd(cmds), NULL);
// 		new->cmd = tokens_to_argv(&start, NULL);
// 		if (!new->cmd)
// 		{
// 			free(new);
// 			free_cmd(cmds);
// 			return (NULL);
// 		}
// 		add_cmd_back(&cmds, new);
// 	}
// 	return (cmds);
// }