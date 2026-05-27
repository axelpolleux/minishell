/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_extand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:45:07 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/26 10:16:18 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	skip_quote(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
		return (true);
	(*i)++;
	return (false);
}

bool	is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

void	add_in(char *input, int *i, int *len, int *type)
{
	if (input[*i + 1] == '<')
	{
		*type = HEREDOC;
		*len = 2;
	}
	else
		*type = RED_IN;
}

void	add_out(char *input, int *i, int *len, int *type)
{
	if (input[*i + 1] == '>')
	{
		*type = APPEND;
		*len = 2;
	}
	else
		*type = RED_OUT;
}

void	new_state(t_data *data, char *input, int *index)
{
	if (data->quote == SQUOT)
	{
		if (input[*index] == '\'')
			data->quote = NQUOT;
	}
	else if (data->quote == DQUOT)
	{
		if (input[*index] == '"')
			data->quote = NQUOT;
	}
}
