/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:50:21 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/15 13:22:39 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_in_en(t_data *data, char *name)
{
	t_env	*env;
	int		i;
	int		len;

	env = data->t_env;
	i = 0;
	len = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->var, name, len) && name[len + 1] == '=')
			return (EXIT_SUCCESS);
		env = env->next;
	}
	return (EXIT_FAILURE);
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
