/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:31:49 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/28 18:18:48 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	flag_identification(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] != '-')
		return (false);
	i++;
	if (str[i] != 'n')
		return (false);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	print_flag(char **args, int start)
{
	int	first_word;

	first_word = 1;
	while (args[start])
	{
		if (ft_strlen(args[start]) != 0)
		{
			if (first_word)
			{
				printf("%s", args[start]);
				first_word = 0;
			}
			else
				printf(" %s", args[start]);
		}
		start++;
	}
}

int	exec_echo(char **args)
{
	int		i;
	bool	new;

	i = 1;
	new = true;
	while (flag_identification(args[i]))
	{
		new = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new)
		printf("\n");
	return (0);
}
