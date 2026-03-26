/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:02:59 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/26 18:01:35 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		data_malloc_error(data);
	data->fd_storage[0] = -1;
	data->fd_storage[1] = -1;
	data->last_fd = -1;
	data->env = NULL;
	data->token = NULL;
	data->cmd = NULL;
	(void)av;
	(void)ac;
	return (data);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mal;
	size_t	aloc;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	aloc = nmemb * size;
	if (aloc == 0 || aloc / nmemb != size)
		return (malloc(0));
	mal = malloc(nmemb * size);
	if (!mal)
		return (NULL);
	ft_memset(mal, 0, nmemb * size);
	return (mal);
}

char	**tab_env(t_env *env)
{
	t_env	*cop;
	char	**tab_env;
	char	*tmp;
	int		i;

	i = -1;
	tab_env = ft_calloc(sizeof(char *), ft_lstsize_e(env) + 1);
	if (!tab_env)
		return (NULL);
	cop = env;
	while (cop)
	{
		tmp = ft_strdup(cop->var);
		if (!tmp)
		{
			free_arr(tab_env);
			return (NULL);
		}
		tab_env[++i] = tmp;
		cop = cop->next;
	}
	return (tab_env);
}
