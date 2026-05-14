/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:50:21 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 11:29:54 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_export(t_data *data, char **cmd)
{
	t_env	*tmp;
	char	**tab_tri_env;
	int		i;

	tmp = data->t_env;
	if (nb_arg(cmd) != 1)
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

int	pars_export(char *cmd)
{
	int		i;

	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
		return (EXIT_FAILURE);
	while (cmd[++i])
	{
		if (cmd[i] == '=')
			return (EXIT_SUCCESS);
		else if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//gerer les pipe "export | " donne rien
int	central_export(t_data *data, char **cmd)
{
	t_env	*tmp;
	int		output;
	int		i;

	i = 0;
	output = 0;
	tmp = data->t_env;
	while (cmd[++i])
	{
		if (pars_export(cmd[i]))
		{
			error_export(cmd[i]);
			output = EXIT_FAILURE;
			continue ;
		}
		manage_export(data, cmd[i]);
	}
	return (output);
}

int	exec_export(t_data *data, char **cmd)
{
	if (only_export(data, cmd))
		return (EXIT_SUCCESS);
	if (central_export(data, cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
