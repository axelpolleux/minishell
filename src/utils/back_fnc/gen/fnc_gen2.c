/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:06:25 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 17:48:08 by ethutin-         ###   ########.fr       */
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

//on pourrait changer le struct pour avoir seulement un ft_lstsize_general
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

int	only_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (line[i] != '\'' && line[i] != '\"')
			return (0);
	return (1);
}

int	full_void(char *line)
{
	int	i;

	i = -1;
	if (line)
	{
		while (line[++i])
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
				return (0);
	}
	return (1);
}
