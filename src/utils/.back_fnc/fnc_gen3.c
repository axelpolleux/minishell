/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:02:59 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/24 10:43:56 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_arg(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

char	**tab_env(t_env *env, int i)
{
	t_env	*cop;
	char	**tab_env;
	char	*tmp;

	tab_env = ft_calloc(sizeof(char *), ft_lstsize_e(env) + 1);
	if (!tab_env)
		return (NULL);
	cop = env;
	while (cop)
	{
		if (cop->export)
		{
			tmp = ft_strdup(cop->var);
			if (!tmp)
			{
				free_arr(tab_env);
				return (NULL);
			}
			tab_env[++i] = tmp;
		}
		else
			cop = cop->next;
	}
	return (tab_env);
}

void	add_to_bottom_cmd(t_cmd **node, t_cmd *new_bot)
{
	t_cmd	*end;

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

char	*var_env(char **env, char *motif, int len)
{
	char	*var;
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], motif, len))
		{
			var = env[i] + len + 1;
			return (var);
		}
	}
	return (NULL);
}

char	*ft_charjoin(char *str, char c)
{
	char	*new_line;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_line = ft_strjoin(str, tmp);
	free(str);
	return (new_line);
}
