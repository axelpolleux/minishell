/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:01:08 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/25 19:45:31 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	double_quotes(t_data *data, t_token **tokens, char *input, int *index)
// {
// 	t_token	*new;
// 	int		i;
// 	int		start;

// 	if (input[*index] != '\"')
// 		return (EXIT_SUCCESS);
// 	i = 1;
// 	while (input[*index + i] && input[*index + i] != 34)
// 		i++;
// 	if (!input[*index + i])
// 		return (error_quote());
// 	start = *index;
// 	new = token_new(input, &start, i + 1, WORD);
// 	if (!new)
// 		data_malloc_error(data);
// 	ft_token_add_back(tokens, new);
// 	(*index) += (i + 1);
// 	return (EXIT_SUCCESS);
// }

// int	single_quotes(t_data *data, t_token **tokens, char *input, int *index)
// {
// 	t_token	*new;
// 	int		i;
// 	int		start;

// 	if (input[*index] != '\'')
// 		return (EXIT_SUCCESS);
// 	i = 1;
// 	while (input[*index + i] && input[*index + i] != '\'')
// 		i++;
// 	if (!input[*index + i])
// 		return (error_quote());
// 	start = *index;
// 	new = token_new(input, &start, i + 1, WORD);
// 	if (!new)
// 		data_malloc_error(data);
// 	ft_token_add_back(tokens, new);
// 	(*index) += (i + 1);
// 	return (EXIT_SUCCESS);
// }

// int	manage_quote(t_data *data, t_token **tokens, char *input, int *index)
// {
// 	if (input[*index] == '"')
// 	{
// 		if (double_quotes(data, tokens, input, index) == EXIT_FAILURE)
// 		{
// 			free_token(*tokens);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	else if (input[*index] == '\'')
// 	{
// 		if (single_quotes(data, tokens, input, index))
// 		{
// 			free_token(*tokens);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	double_quotes(char *input, int *index)
// {
// 	int		i;

// 	if (input[*index] != '\"')
// 		return (EXIT_SUCCESS);
// 	i = 1;
// 	while (input[*index + i] && input[*index + i] != '\"')
// 		i++;
// 	if (!input[*index + i])
// 		return (error_quote());
// 	return (EXIT_SUCCESS);
// }

// int	single_quotes(char *input, int *index)
// {
// 	int		i;

// 	if (input[*index] != '\'')
// 		return (EXIT_SUCCESS);
// 	i = 1;
// 	while (input[*index + i] && input[*index + i] != '\'')
// 		i++;
// 	if (!input[*index + i])
// 		return (error_quote());
// 	return (EXIT_SUCCESS);
// }

// int	manage_quote(t_token **tokens, char *input, int *index)
// {
// 	if (input[*index] == '"')
// 	{
// 		if (double_quotes(input, index))
// 		{
// 			free_token(*tokens);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	else if (input[*index] == '\'')
// 	{
// 		if (single_quotes(input, index))
// 		{
// 			free_token(*tokens);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }
