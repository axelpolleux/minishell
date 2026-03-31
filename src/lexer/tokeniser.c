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


#include "minishell.h"
#include "../../includes/lib/minishell.h"


// int	is_it_quote(int c)
// {
// 	if (c == 34 || c == 39)
// 		return (1);
// 	return (0);
// }
//
// int	is_it_space(int c)
// {
// 	if (c == ' ' || (c >= 9 && c <= 13))
// 		return (1);
// 	return (0);
// }

char	*select_quote(char *input)
{
	char	*res;
	int		i;

	i = 0;
	if (!(input[i] == 34 || input[i] == 39))
	return (res);
}

void	tokeniser(char *input, char *delim)
{
	t_token	token;


}