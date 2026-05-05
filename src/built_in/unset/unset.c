/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:16:32 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 18:01:47 by ethutin-         ###   ########.fr       */
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
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				data->t_env = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp->var);
			free(tmp->key);
			free(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	exec_unset(t_data *data, char **cmd)
{
	int		i;

	i = 1;
	if (nb_arg(cmd) < 2)
		return (EXIT_SUCCESS);
	while (cmd[i])
	{
		unset_place(data, cmd[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
