/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:53:33 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/17 11:19:00 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closes(int fd, int *fd_storage)
{
	if (fd >= 0)
		close(fd);
	if (fd_storage)
	{
		if (fd_storage[0] >= 0)
			close(fd_storage[0]);
		if (fd_storage[1] >= 0)
			close(fd_storage[1]);
	}
}

int	srch_cmd(char *s, char c)
{
	while (*s && *s != '\0')
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

t_env	*last_node(t_env *nod)
{
	while (nod && nod->next)
		nod = nod->next;
	return (nod);
}

void	add_to_bottom(t_env **node, t_env *new_bot)
{
	t_env	*end;

	if (!new_bot)
		return ;
	if (!*node)
	{
		*node = new_bot;
		return ;
	}
	end = *node;
	while (end->next)
		end = end->next;
	end->next = new_bot;
	new_bot->prev = end;
}


