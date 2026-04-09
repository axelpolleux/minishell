/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/09 16:44:14 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/lib/minishell.h"
#include "libft/libft.h"

void	skip_spaces(char *input, int *index)
{
	while (is_space(input[*index]))
		(*index)++;
}

void	add_in(char *input, t_token **tokens, int *index)
{
	int	type;
	int	len;

	len = 1;
	if (input[*index] == '|')
		type = PIPE;
	else if (input[*index] == '<')
	{
		if (input[*index + 1] == '<')
		{
			type = HEREDOC;
			len = 2;
		}
		else
			type = RED_IN;
	}
	else
		type = WORD;
	ft_token_add_back(tokens, token_new(ft_substr(input, *index, len), type));
	(*index) += len;
}

void	add_out(char *input, t_token **tokens, int *index)
{
	int	type;
	int	len;

	len = 1;
	if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
		{
			type = APPEND;
			len = 2;
		}
		else
			type = RED_OUT;
	}
	else
		type = WORD;
	ft_token_add_back(tokens, token_new(ft_substr(input, *index, len), type));
	(*index) += len;
}

void	add_word(char *input, t_token **tokens, int *index)
{
	int		len;
	t_token	*token;

	len = 0;
	while (input[*index + len] && !is_space(input[*index + len])
		&& !ft_strchr("|<>", input[*index + len]))
		len++;
	token = token_new(ft_substr(input, *index, len), WORD);
	ft_token_add_back(tokens, token);
	(*index) += len;
}

t_token	*tokeniser(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		else if (ft_strchr("|<", input[i]))
			add_in(input, &tokens, &i);
		else if (input[i] == 34)
			double_quotes(input, &tokens, &i);
		else if (ft_strchr(">", input[i]))
			add_out(input, &tokens, &i);
		else if (!is_space(input[i]))
			add_word(input, &tokens, &i);
	}
	display_tokens(tokens);
	free_tokens(tokens);
	return (tokens);
}
