/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/28 12:01:16 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "minishell.h"
#include "../../includes/lib/minishell.h"


char	*select_quote(char *input)
{
	char	*res;
	int		i;

	(void)res;
	res = NULL;
	i = 0;
	printf("Quote detected\n");
	if (!(input[i] == 34 || input[i] == 39))
		return (0);
	return (res);
}

void	tokeniser(char *input)
{
	int		i;
	t_token	res;

	i = 0;
	(void)res;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			select_quote(input);
		i++;
	}
}