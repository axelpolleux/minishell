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

// int is_it_space(int c)
// {
// 	if (c == ' ' || (c >= 9  && c <= 12))
// 		return (1);
// 	return (0);
// }

// int is_quote(int c)
// {
// 	if (c == 34 || c == 39)
// 		return (1);
// 	return (0);
// }

void	typer(t_token token)
{
	if (ft_strcmp(token->cmd, "|"))
		token->type = PIPE;
}

void	tokeniser(char *input)
{
	t_token	token;
	char	*res;
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}

}