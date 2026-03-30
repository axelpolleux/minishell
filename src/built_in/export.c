/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:50:21 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/28 16:04:49 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tri_alpha(t_env *env)
{
	char	**arr;
	char	*tmp;
	int		i;
	int		j;

	arr = tab_env(env);
	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
	}
	return (arr);
}

void	export_central(t_data *data)
{
	char	**tab_tri_env;
	int		i;

	i = -1;
	tab_tri_env = tri_alpha(data->t_env);
	if (!tab_tri_env)
		data_malloc_error(data);
	while (tab_tri_env[++i])
		printf("declare -x %s\n", tab_tri_env[i]);
	free_arr(tab_tri_env);
}
