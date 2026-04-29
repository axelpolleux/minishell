/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:58:04 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/27 13:55:35 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **fill_cmd(t_token *token)
// {
// 	t_token	*tmp;
// 	char	**cmd;
// 	int		len;

// 	len = 0;
// 	tmp = token;
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		len++;
// 		token = token->next;
// 	}
// 	cmd = ft_calloc(sizeof(char *), len + 1);
// 	if (!cmd)
// 		return (NULL);
// 	cmd[len] = "\0";
// 	while (token && token->type != PIPE)
// 	{
// 		tmp->cmd = token->cmd;
// 		token = token->next;
// 	}
// 	if (token)
// 		token = token->next;
// 	return (cmd);
// }

// t_cmd	*cmd_new(t_token *token)
// {
// 	t_cmd	*new;

// 	if (!token)
// 		return (NULL);
// 	new = ft_calloc(sizeof(t_cmd), 1);
// 	if (!new)
// 		return (NULL);
// 	new->type = token->type;
// 	new->prev = NULL;
// 	new->next = NULL;
// 	new->cmd = fill_cmd(token);
// 	if (!new->cmd)
// 		return (NULL);
// 	new->cmd_path = (NULL);
// 	new->full_cmd = (NULL);
// 	return (new);
// }

// t_cmd	*init_cmd(t_data *data, t_token *token)
// {
// 	t_token	*tmp_tok;
// 	t_cmd	*cmd;
// 	int	index;

// 	tmp_tok = token;
// 	cmd = NULL;
// 	index = 0;
// 	while (tmp_tok)
// 	{
// 		cmd = cmd_new(tmp_tok);
// 		if (!cmd)
// 			data_malloc_error(data);
// 		add_to_bottom_cmd(&data->cmd, cmd);
// 	}
// 	return (cmd); 
// }
