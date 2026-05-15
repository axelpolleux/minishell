/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 15:30:11 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_env(t_data *data, char *motif)
{
	t_env	*tmp;
	char	*path;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, motif))
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
		i++;
	}
	return (0);
}
