/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/28 10:47:14 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char *input, int *index)
{
	while (is_space(input[*index]))
		(*index)++;
}

bool	quote_state(t_data *data, char *input, int *index, bool *quoted)
{
	if (data->quote == NQUOT)
	{
		if (is_space(input[*index]) || ft_strchr("|<>", input[*index]))
			return (true);
		if (input[*index] == '\'')
		{
			data->quote = SQUOT;
			*quoted = true;
		}
		else if (input[*index] == '"')
		{
			data->quote = DQUOT;
			*quoted = true;
		}
	}
	else
		new_state(data, input, index);
	return (false);
}

bool	add_word(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token		*new;
	int			start;
	bool		quoted;

	start = *index;
	data->quote = NQUOT;
	quoted = false;
	while (input[*index])
	{
		if (quote_state(data, input, index, &quoted))
			break ;
		(*index)++;
	}
	if (data->quote != NQUOT)
		return (error_pars(0));
	new = token_new(input + start, *index - start, WORD, quoted);
	if (!new)
	{
		data->exit = -2;
		return (true);
	}
	ft_token_add_back(tokens, new);
	return (false);
}

bool	add_all(t_data *data, t_token **tokens, char *input, int *i)
{
	t_token			*new;
	int				type;
	int				len;

	len = 1;
	if (input[*i] == '|')
		type = PIPE;
	else if (input[*i] == '<')
		add_in(input, i, &len, &type);
	else
		add_out(input, i, &len, &type);
	new = token_new(input + *i, len, type, false);
	if (!new)
	{
		data->exit = -2;
		return (false);
	}
	ft_token_add_back(tokens, new);
	*i += len;
	return (true);
}

t_token	*tokeniser(t_data *data, char *input)
{
	t_token	*tokens;
	int		index;

	index = 0;
	tokens = NULL;
	while (input[index])
	{
		skip_spaces(input, &index);
		if (!input[index])
			break ;
		if (ft_strchr("|<>", input[index]))
		{
			if (!add_all(data, &tokens, input, &index))
				return (NULL);
		}
		else if (add_word(data, &tokens, input, &index))
			return (NULL);
	}
	return (tokens);
}
