/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:36:37 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 17:50:36 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_champ_env(t_data *data, char **new_var, char **new_arg, char **new_key)
{
	*new_var = ft_strdup(data->line_env);
	if (!*new_var)
		return (EXIT_FAILURE);
	*new_arg = ft_substr(data->line_env, only_key(data->line_env) + 1, INT_MAX);
	if (!*new_arg)
	{
		free(*new_var);
		return (EXIT_FAILURE);
	}
	*new_key = ft_substr(data->line_env, 0, only_key(data->line_env));
	if (!*new_key)
	{
		free(*new_var);
		free(*new_arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	no_minim_env(char **env)
{
	int		i;
	int		error;

	if (!env || !(*env))
		return (-1);
	error = 0;
	i = -1;
	if (not_in_original_en(env, PWD))
		error += 2;
	if (not_in_original_en(env, OLDPWD))
		error += 1;
	return (error);
}
