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


char	*select_quote(char *input)
{
	char	*res;
	int		i;

	i = 0;
	if (!(input[i] == 34 || input[i] == 39))
		return (0);
	return (res);
}

t_token	tokeniser(char *input, char *delim)
{
	int		i;
	t_token	res;

	i = 0;
	while (input[i] && !ft_strchr(delim, input[i]))
	{
		printf("");
		i++;
	}

}