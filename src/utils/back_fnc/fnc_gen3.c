/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:42:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/30 11:36:50 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_e(t_env *lst)
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

void	free_cmd(t_cmd *node)
{
	t_cmd	*tmp;

	if (node == NULL)
		return ;
	while (node)
	{
		tmp = (node)->next;
		if (tmp->cmd)
			free_arr(tmp->cmd);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->full_cmd)
			free(tmp->full_cmd);
		free(node);
		node = tmp;
	}
	node = NULL;
}