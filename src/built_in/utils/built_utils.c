/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/21 11:22:01 by ethutin-         ###   ########.fr       */
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

char	*get_var_env(t_data *data, char *motif, int len)
{
	t_env	*tmp;
	char	*path;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, motif, len))
		{
			path = tmp->arg;
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_builtin(char **built_in, char *cmd)
{
	int	i;

	i = 0;
	if (built_in == NULL)
		return (0);
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd))
			return (1);
	}
	return (0);
}
