/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:16:32 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/25 13:53:04 by ethutin-         ###   ########.fr       */
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
			free(tmp->arg);
			free(tmp->key);
			free(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	exec_unset(t_data *data, char **args)
{
	int		i;

	i = 0;
	if (args == NULL)
		return (EXIT_SUCCESS);
	while (args[i])
	{
		unset_place(data, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
