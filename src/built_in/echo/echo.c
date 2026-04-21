/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:31:49 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/20 14:15:11 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_flag(char **cmd, int start)
{
	int	firts_word;

	firts_word = 1;
	while (cmd[start])
	{
		if (ft_strlen(cmd[start]) != 0)
		{
			if (firts_word)
			{
				printf("%s", cmd[start]);
				firts_word = 0;
			}
			else
				printf(" %s", cmd[start]);
		}
		start++;
	}
}

int	exec_echo(char **cmd)
{
	int	i;
	int	firts_word;

	firts_word = 1;
	i = 0;
	if (!(ft_strcmp(cmd[1], "-n")))
		print_flag(cmd, 2);
	else
	{
		while (cmd[++i])
		{
			if (ft_strlen(cmd[i]) != 0)
			{
				if (firts_word)
				{
					printf("%s", cmd[i]);
					firts_word = 0;
				}
				else
					printf(" %s", cmd[i]);
			}
		}
		printf("\n");
	}
	return (0);
}
