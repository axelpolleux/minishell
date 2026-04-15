/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:42:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/14 15:02:46 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_e(t_env *lst)
{
	size_t	len_lst;

	len_lst = 0;
	while (lst)
	{
		if (lst->export)
			len_lst++;
		lst = lst->next;
	}
	return (len_lst);
}

int	ft_lstsize_t(t_token *lst)
{
	size_t	len_lst;

	len_lst = 0;
	while (lst)
	{
		len_lst++;
		lst = lst->next;
	}
	return (len_lst);
}

int	ft_lstsize_c(t_cmd *lst)
{
	size_t	len_lst;

	len_lst = 0;
	while (lst)
	{
		len_lst++;
		lst = lst->next;
	}
	return (len_lst);
}

void	free_token(t_token *node)
{
	t_token	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
		free(node);
		node = tmp;
	}
	node = NULL;
}

void	free_env(t_env *node)
{
	t_env	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
		free(node->var);
		free(node);
		node = tmp;
	}
	node = NULL;
}
