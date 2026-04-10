/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:50:21 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/10 11:58:19 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_in_en(char *cmd)
{
	int i;

	i = 0;

	if in
	
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

int only_export(t_data *data, char **cmd)
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

int	pars_export(char *cmd)
{
	char	*key;
	int		i;

	i = -1;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (EXIT_FAILURE);
	while (cmd[++i])
	{
		if (cmd[i] == '=')
				return(EXIT_SUCCESS);
		else if (cmd[i] != ft_isalpha && cmd[i] != '_')
			return (EXIT_FAILURE);
	}	
	return	(EXIT_SUCCESS);
}
int	central_export(t_data *data, char **cmd, int i)
{
	t_env	*tmp;
	int		output;

	output = 0;
	tmp = data->t_env;
	while (cmd[++i])
	{
		if	(pars_export(cmd[i]))
		{
			error_exit(EXP_ER, P_ERROR, 2); 
			output = EXIT_FAILURE;
		}

	}
	return (output);
}

int	exec_export(t_data *data, char **cmd)
{
	if (!only_export(data, cmd));
		return (EXIT_SUCCESS);
	if (central_export(data, cmd, 0))
		return(EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

