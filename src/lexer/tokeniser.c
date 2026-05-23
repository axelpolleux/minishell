/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 11:06:42 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/22 14:29:19 by ethutin-         ###   ########.fr       */
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
	if (input[*index] == '|' && ++data->pipe)
		type = PIPE;
	else if (input[*index] == '<' && input[*index + 1] == '<')
	{
		type = HEREDOC;
		len = 2;
	}
	else if (input[*index] == '<')
		type = RED_IN;
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
		if (input[*index + 1] && input[*index + 1] == '>')
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

// void	add_word(t_data *data, t_token **tokens, char *input, int *index)
// {
// 	t_token	*new;
// 	int		start;
// 	int		i;

// 	start = *index;
// 	i = *index;
// 	while (input[i] && !is_space(input[i]) && !ft_strchr("|<>", input[i]))
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 		{
// 			if (skip_quote(input, &i))
// 			{
// 				free_token(*tokens);
// 				ft_putstr_fd(QUOT_ER, 2);
// 				return ;
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	new = token_new(input, &start, i - start, WORD);
// 	if (!new)
// 		data_malloc_error(data);
// 	ft_token_add_back(tokens, new);
// 	*index = i;
// }

int	add_word(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		start;
	int		i;

	start = *index;
	i = *index;
	while (input[i] && !is_space(input[i]) && !ft_strchr("|<>", input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (skip_quote(input, &i))
			{
				free_token(*tokens);
				*tokens = NULL;
				return (error_quote());
			}
		}
		else
			i++;
	}
	new = token_new(input, &start, i - start, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	*index = i;
	return (EXIT_SUCCESS);
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
		if (ft_strchr("|<", input[index]))
			add_in(data, &tokens, input, &index);
		else if (manage_quote(&tokens, input, &index))
			return (NULL);
		else if (input[index] == '>')
			add_out(data, &tokens, input, &index);
		else if (add_word(data, &tokens, input, &index))
			return (NULL);
	}
	return (tokens);
}
