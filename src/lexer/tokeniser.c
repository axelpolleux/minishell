/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/01 19:15:45 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/lib/minishell.h"
#include "../../includes/libft/libft.h"

int	is_space(int c)
{
	if (c == ' ' && (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	skip_spaces(char *input, int *index)
{
	while (is_space(input[*index]))
		(*index)++;
}

void	add_operator(char *input, t_token token, int *index)
{
	return ;
}

void	add_word(char *input, t_token token, int *index)
{
	int	len;

	len = 0;
	while (input[*index]
		&& !is_space(input[*index])
		&& !ft_strchr("|<>", input[*index]))
	{
		(*index)++;
		len++;
	}
	token.cmd = ft_substr(input, *index, len);
	token.type = WORD;
}

t_token	*tokeniser(char *input)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (ft_strchr("|<>", input[i]))
			add_operator(input, &token, &i);
		else
			add_word(input, &token, &i);
		i++;
	}
	return (token);
}
