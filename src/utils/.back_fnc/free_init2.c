/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:20:04 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/23 18:32:20 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *line, int export)
{
	t_env	*new_node;
	char	*key;
	int		i;

	i = 0;
	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->var = line;
	while (line[i] != '=')
		i++;
	new_node->arg = line + i + 1;
	key = ft_substr(line, 0, i);
	if (!key)
		return (NULL);
	new_node->key = key;
	new_node->export = export;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

// t_env	*new_env_n_on(char *line, int export)
// {
// 	t_env	*new_node;
// 	int		i;

// 	i = 0;
// 	new_node = ft_calloc(sizeof(t_env), 1);
// 	if (new_node == NULL)
// 		return (NULL);
// 	new_node->var = line;
// 	new_node->arg = NULL;
// 	new_node->export = export;
// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	return (new_node);
// }

char	**init_built(void)// on pourrait bien mieux faire, a refaire 
{
	char	**built_in;

	built_in = ft_split("echo cd pwd export unset env exit", ' ');
	if (!built_in)
		return (NULL);
	return (built_in);
}
