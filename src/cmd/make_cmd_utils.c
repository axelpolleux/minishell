/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:44:26 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/01 22:05:29 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(int type)
{
	if (type == RED_IN || type == RED_OUT
		|| type == APPEND || type == HEREDOC)
		return (true);
	return (false);
}

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

t_cmd	*new_cmd_node(t_data *data)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
	{
		data->exit = -2;
		return (NULL);
	}
	new->input = -1;
	new->output = -1;
	new->executable = 1;
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

int	new_redirection(t_data *data, t_cmd *cmd, int type, char *file)
{
	t_redir_her	*redir;
	char		*tmp;

	redir = ft_calloc(sizeof(t_redir_her), 1);
	if (!redir)
	{
		data->exit = -2;
		return (EXIT_FAILURE);
	}
	(void) file;
	tmp = ft_strdup("");
	if (!tmp)
	{
		data->exit = -2;
		free(redir);
		return (EXIT_FAILURE);
	}
	redir->type = type;
	redir->file = tmp;
	redir->fd = -1;
	if (!cmd->redir)
		cmd->redir = redir;
	else
		add_redir_back(&cmd->redir, redir);
	return (EXIT_SUCCESS);
}
