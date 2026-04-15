/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:59:12 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/14 15:00:37 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->t_env;
	while (tmp)
		printf("%s\n", tmp->var);
	return (EXIT_SUCCESS);
}
