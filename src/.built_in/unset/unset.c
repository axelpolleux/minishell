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
		if (!ft_strcmp(tmp->key, motif))
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

static int	is_valid_id(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	exec_unset(t_data *data, char **args)
{
	int		i;
	int		res;

	i = 1;
	res = EXIT_SUCCESS;
	if (args == NULL)
		return (EXIT_SUCCESS);
	while (args[i])
	{
		if (!is_valid_id(args[i]))
		{
			ft_putstr_fd("minichevre: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
			res = 2;
		}
		else
			unset_place(data, args[i]);
		i++;
	}
	return (res);
}
