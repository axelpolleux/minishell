/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/09 12:05:04 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_built(void)// on  pourrait plus securiser
{
	char    **built_in;

	built_in = ft_split("echo cd pwd export unset env exit", ' ');
	if (!built_in)
		return (NULL);
	return (built_in);
}

int nb_arg(char **ar)
{
	int i;

	i = 0;
	while(ar[i])
		i++;
	return(i);
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
