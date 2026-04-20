/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:02:59 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/17 11:20:42 by ethutin-         ###   ########.fr       */
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




