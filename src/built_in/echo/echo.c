/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:31:49 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/25 14:46:41 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_flag(char **args, int start)
{
	int	firts_word;

	firts_word = 1;
	while (args[start])
	{
		if (ft_strlen(args[start]) != 0)
		{
			if (firts_word)
			{
				printf("%s", args[start]);
				firts_word = 0;
			}
			else
				printf(" %s", args[start]);
		}
		start++;
	}
}

void	print_words(char **args, int *i, int *first_word)
{	
	while (args[++*(i)])
	{
		if (ft_strlen(args[*(i)]) != 0)
		{
			if (*(first_word))
			{
				printf("%s", args[*(i)]);
				*(first_word) = 0;
			}
			else
				printf(" %s", args[*(i)]);
			}
	}
	printf("\n");
}

int	exec_echo(char **args)
{
	int	i;
	int	firts_word;

	if (args == NULL)
	{
		printf("\n");
		return (0);
	}
	firts_word = 1;
	i = -1;
	if (!(ft_strcmp(args[0], "-n")))
		print_flag(args, 1);
	else
		print_words(args, &i, &firts_word);
	return (0);
}
