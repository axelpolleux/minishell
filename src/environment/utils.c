/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:01:58 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/24 10:48:43 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key_len(char *line, char *name)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	if (!ft_isalpha(line[i]) && line[i] != '_')
		return (0);
	while (ft_isalnum(line[i]) || line[i] == '_')
	{
		if (i >= PATH_MAX - 1)
			break ;
		name[i] = line[i];
		i++;
	}
	name[i] = '\0';
	return (i);
}

// int	pars_export(char *cmd)
// {
// 	int		i;

// 	i = 0;
// 	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
// 		return (0);
// 	while (cmd[++i])
// 	{
// 		if (cmd[i] == '=')
// 			return (i);
// 		else if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
// 			return (0);
// 	}
// 	return (i);
// }
