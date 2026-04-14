/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/14 15:04:44 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_built(void)// on  pourrait plus securiser
{
	char	**built_in;

	built_in = ft_split("echo cd pwd export unset env exit", ' ');
	if (!built_in)
		return (NULL);
	return (built_in);
}

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

t_env	*new_env_n_on(char *line, int export)
{
	t_env	*new_node;
	int		i;

	i = 0;
	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->var = line;
	new_node->arg = NULL;
	new_node->export = export;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
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
