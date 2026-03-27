/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/27 16:17:42 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_words(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		printf("[%s] ", input[i]);
		i++;
	}
	printf("\n");
}

int	main_parser(char *input)
{
	char	**res;

	res = token_split(input);
	display_words(res);
	free(res);
	return (1);
}
