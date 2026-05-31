/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:50:21 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/25 19:47:27 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_export(t_data *data, char **args)
{
	t_env	*tmp;
	char	**tab_tri_env;
	int		i;

	tmp = data->t_env;
	if (nb_arg(args) != 1)
		return (0);
	tab_tri_env = tri_alpha(tmp);
	if (!tab_tri_env)
		data_malloc_error(data);
	i = -1;
	while (tab_tri_env[++i])
		printf("declare -x %s\n", tab_tri_env[i]);
	free_arr(tab_tri_env);
	return (1);
}

int	pars_export(char *args)
{
	int		i;

	i = 0;
	if (!ft_isalpha(args[i]) && args[i] != '_')
		return (EXIT_FAILURE);
	while (args[++i])
	{
		if (args[i] == '=')
			return (EXIT_SUCCESS);
		else if (!ft_isalnum(args[i]) && args[i] != '_')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	central_export(t_data *data, char **args)
{
	int		output;
	int		i;

	i = 0;
	output = EXIT_SUCCESS;
	if (args == NULL)
		return (output);
	while (args[++i])
	{
		if (pars_export(args[i]))
		{
			error_export(args[i]);
			output = EXIT_FAILURE;
			continue ;
		}
		manage_export(data, args[i]);
	}
	return (output);
}

int	exec_export(t_data *data, char **args)
{
	if (only_export(data, args))
		return (EXIT_SUCCESS);
	if (central_export(data, args))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
