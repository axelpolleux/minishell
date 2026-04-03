/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/03 16:58:01 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	skip_spaces(char *input, int *index)
{
	while (is_space(input[*index]))
		(*index)++;
}

void	add_operator(char *input, t_token *token, int *index)
{
	(void)input;
	(void)token;
	(void)index;
	printf("Operator detected\n");
	(*index)++;
	return ;
}

void	add_word(char *input, t_token *token, int *index)
{
	int	len;

	len = 0;
	while (input[*index + len] && !is_space(input[*index + len])
		&& !ft_strchr("|<>", input[*index + len]))
		len++;
	token->cmd = ft_substr(input, *index, len);
	token->type = WORD;
	(*index) += len;
}

t_token	tokeniser(char *input)
{
	int		i;
	t_token	token;

	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (ft_strchr("|<>", input[i]))
			add_operator(input, &token, &i);
		else if (!is_space(input[i]))
			add_word(input, &token, &i);
	}
	display_tokens(token);
	return (token);
}
