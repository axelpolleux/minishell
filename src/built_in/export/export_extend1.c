/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extend1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:37:04 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 18:01:33 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_export(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->export)
			count++;
		env = env->next;
	}
	return (count);
}

void	change_arg(t_data *data, char *line, char *name, int start)
{
	t_env	*tmp;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->key))
		{
			if (realoc_arg(tmp, line, name, start))
				data_malloc_error(data);
			return ;
		}
		tmp = tmp->next;
	}
}

char	**tri_alpha(t_env *env)
{
	char	**arr;
	char	*tmp;
	int		i;
	int		j;

	arr = tab_env(env, -1);
	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		j = i;
		while (arr[++j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	return (arr);
}

void	manage_export(t_data *data, char *line)
{
	char	*name;
	int		key;

	key = only_key(line);
	if (key == 0)
	{
		make_export(data, line);
		return ;
	}
	name = ft_substr(line, 0, key);
	if (!name)
		data_malloc_error(data);
	if (key_in_env(data, name))
	{
		change_arg(data, line, name, key);
		return ;
	}
	free(name);
	env_new_node(data, line);
}

void	env_new_node(t_data *data, char *line)
{
	t_env	*new;
	char	*new_var;
	char	*new_arg;
	char	*new_key;

	new_var = NULL;
	new_arg = NULL;
	new_key = NULL;
	data->line_env = line;
	if (init_champ_env(data, &new_var, &new_arg, &new_key))
		init_env_fail(data, new_var, new_arg, new_key);
	new = new_env(new_var, new_arg, new_key, 1);
	if (!new)
		init_env_fail(data, new_var, new_arg, new_key);
	add_to_bottom_env (&data->t_env, new);
}
