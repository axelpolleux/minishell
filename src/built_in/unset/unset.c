/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:16:32 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/14 15:01:58 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_place(t_data *data, char *motif)
{
	t_env	*tmp;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, motif, ft_strlen(motif)))
		{
			if (tmp->export)
				tmp->export = 0;
			break ;
		}
		tmp = tmp->next;
	}
}

int	exec_unset(t_data *data, char **cmd)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = data->t_env;
	while (cmd[++i])
	{
		unset_place(data, cmd[i]);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
