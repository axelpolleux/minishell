/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:20:04 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 18:44:32 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *new_var, char *new_arg, char *new_key, int export)
{
	t_env	*new_node;

	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->var = new_var;
	new_node->arg = new_arg;
	new_node->key = new_key;
	new_node->export = export;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

char	**init_built(void)
{
	char	**built_in;

	built_in = ft_calloc(sizeof(char *), 8);
	if (!built_in)
		return (NULL);
	built_in[0] = "echo";
	built_in[1] = "cd";
	built_in[2] = "pwd";
	built_in[3] = "export";
	built_in[4] = "unset";
	built_in[5] = "env";
	built_in[6] = "exit";
	built_in[7] = NULL;
	return (built_in);
}

t_env	*make_new_env_name(char *line, int export)
{
	t_env	*new_node;
	char	*new_var;
	char	*name;

	new_var = ft_strdup(line);
	if (!new_var)
		return (NULL);
	name = ft_strdup(line);
	if (!name)
	{
		free(new_var);
		return (NULL);
	}
	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
	{
		free(new_var);
		free(name);
		return (NULL);
	}
	new_node->var = new_var;
	new_node->arg = NULL;
	new_node->key = name;
	new_node->export = export;
	return (new_node);
}
