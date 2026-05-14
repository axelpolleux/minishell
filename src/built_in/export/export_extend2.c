/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extend2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:14:51 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 18:01:01 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_export(t_data *data, char *key)
{
	t_env	*tmp;
	t_env	*new;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			tmp->export = 1;
			return ;
		}
		tmp = tmp->next;
	}
	new = make_new_env_name(key, 1);
	if (!new)
		data_malloc_error(data);
	add_to_bottom_env(&data->t_env, new);
	return ;
}

int	realoc_arg(t_env *tmp, char *line, char *name, int start)
{
	char	*new_var;
	char	*new_arg;

	free(tmp->var);
	free(tmp->key);
	free(tmp->arg);
	new_var = ft_strdup(line);
	if (!new_var)
	{
		free(name);
		return (EXIT_FAILURE);
	}
	new_arg = ft_strdup(new_var + start + 1);
	if (!new_var)
	{
		free(name);
		free(new_var);
		return (EXIT_FAILURE);
	}
	tmp->var = new_var;
	tmp->arg = new_arg;
	tmp->key = name;
	tmp->export = 1;
	return (EXIT_SUCCESS);
}
