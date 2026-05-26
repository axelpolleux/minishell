/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junie <junie@jetbrains.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:50:00 by junie             */
/*   Updated: 2026/05/26 12:50:00 by junie             */
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
