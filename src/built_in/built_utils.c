/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/03 14:41:33 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
