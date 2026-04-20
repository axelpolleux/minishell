/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:37:04 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/16 18:31:42 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_arg(t_env *tmp, char *cmd, int i)
{
	free(tmp->arg);
	free(tmp->var);
	tmp->var = ft_strdup(cmd);
	tmp->arg = ft_substr(cmd, i + 1, ft_strlen(cmd));
	tmp->export = 1;
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

int	only_export(t_data *data, char **cmd)
{
	t_env	*tmp;
	char	**tab_tri_env;
	int		i;

	tmp = data->t_env;
	if (nb_arg(cmd) != 1)
		return (EXIT_FAILURE);
	tab_tri_env = tri_alpha(tmp);
	if (!tab_tri_env)
		data_malloc_error(data);
	i = -1;
	while (tab_tri_env[++i])
		printf("declare -x %s\n", tab_tri_env[i]);
	free_arr(tab_tri_env);
	return (EXIT_SUCCESS);
}

int	name_arg(t_data *data, t_env *tmp, char *cmd)
{
	t_env	*new;
	char	*replace;
	int		i;	

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
		{
			replace = ft_substr(cmd, 0, i);
			if (!replace)
				data_malloc_error(data);
			if (not_in_en(data, replace))
			{
				new = new_env(ft_strdup(cmd), 1);
				if (!new)
					data_malloc_error(data);
				add_to_bottom(&data->t_env, new);
			}
			else
				change_arg(tmp, cmd, i);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

void	only_name(t_data *data, t_env *tmp, char *cmd)
{
	if (not_in_en(data, cmd))
		return ;
	else
		tmp->export = 1;
}
