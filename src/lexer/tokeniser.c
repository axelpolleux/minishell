/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/05 17:32:04 by apolleux         ###   ########.fr       */
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

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	add_operator(char *input, t_token **tokens, int *index)
{
	int	type;
	int	len;

	len = 1;
	if (input[*index] == '|')
		type = PIPE;
	else if (input[*index] == '<')
		if (input[*index + 1] == '<')
		{
			type = HEREDOC;
			len = 2;
		}
		else
			type = RED_IN;
	else if (input[*index] == '>')
		if (input[*index + 1] == '>')
		{
			type = APPEND;
			len = 2;
		}
		else
			type = RED_OUT;
	else
		type = WORD;
	ft_token_add_back(tokens, token_new(ft_substr(input, *index, len), type));
	(*index) += len;
}

void	add_word(char *input, t_token **tokens, int *index)
{
	int	len;

	len = 0;
	while (input[*index + len] && !is_space(input[*index + len])
		&& !ft_strchr("|<>", input[*index + len]))
		len++;
	ft_token_add_back(tokens, token_new(ft_substr(input, *index, len), WORD));
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
		if (ft_strchr("|<>", input[i]))
			add_operator(input, &tokens, &i);
		else if (!is_space(input[i]))
			add_word(input, &tokens, &i);
	}
	display_tokens(tokens);
	return (tokens);
}
