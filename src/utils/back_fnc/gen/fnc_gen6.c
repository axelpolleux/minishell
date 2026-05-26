/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junie <junie@jetbrains.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:45:00 by junie             */
/*   Updated: 2026/05/26 12:45:00 by junie             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_back(t_cmd **lst, t_cmd *new)
{
	add_to_bottom_cmd(lst, new);
}

void	add_redir_back(t_redir_her **lst, t_redir_her *new)
{
	t_redir_her	*last;

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
}
