/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/20 10:05:14 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char *input, int *index)
{
	while (is_space(input[*index]))
		(*index)++;
}

void	add_in(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		type;
	int		len;

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
	new = token_new(input, index, len, type);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += len;
}

void	add_out(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		type;
	int		len;

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
	new = token_new(input, index, len, type);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += len;
}

void	add_word(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		len;

	len = 0;
	while (input[*index + len] && !is_space(input[*index + len])
		&& !ft_strchr("|<>", input[*index + len])
		&& (input[*index + len] != '"' && input[*index + len] != '\''))
		len++;
	new = token_new(input, index, len, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += len;
}

t_token	*tokeniser(t_data *data, char *input)
{
	int		index;
	t_token	*tokens;

	index = 0;
	tokens = NULL;
	while (input[index])
	{
		skip_spaces(input, &index);
		if (!input[index])
			break ;
		else if (ft_strchr("|<", input[index]))
			add_in(data, &tokens, input, &index);
		else if (input[index] == '"')
			double_quotes(data, &tokens, input, &index);
		else if (input[index] == '\'')
			single_quotes(data, &tokens, input, &index);
		else if (ft_strchr(">", input[index]))
			add_out(data, &tokens, input, &index);
		else if (!is_space(input[index]))
			add_word(data, &tokens, input, &index);
	}
	free(data->line);
	return (tokens);
}
