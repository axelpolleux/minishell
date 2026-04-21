/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:50:21 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/21 11:14:30 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	central_export(t_data *data, char **cmd, int i)
{
	t_env	*tmp;
	int		output;

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
		if (!name_arg(data, tmp, cmd[i]))
			only_name(data, tmp, cmd[i]);
	}
	return (output);
}

int	exec_export(t_data *data, char **cmd)
{
	if (!only_export(data, cmd))
		return (EXIT_SUCCESS);
	if (central_export(data, cmd, 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
