/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:01:08 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/08 16:29:02 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		i;
	int		start;

	if (input[*index] != '\"')
		return (0);
	i = 1;
	while (input[*index + i] && input[*index + i] != 34)
		i++;
	if (!input[*index + i])
	{
		ft_putstr_fd(QUOT_ER, 2);
		i++;
		return (0);
	}
	start = *index;
	new = token_new(input, &start, i + 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
	return (1);
}

int	single_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		i;
	int		start;

	if (input[*index] != '\'')
		return (0);
	i = 1;
	while (input[*index + i] && input[*index + i] != '\'')
		i++;
	if (!input[*index + i])
		return (0);
	start = *index;
	new = token_new(input, &start, i + 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
	return (1);
}

int	quotes_manager(t_data *data, t_token **tokens, char *input, int *index)
{
	// double_quotes(data, &tokens, input, &index);
	// single_quotes(data, &tokens, input, &index);
	if (input[*index] == '"' && !double_quotes(data, tokens, input, index))
		return (0);
	else if (input[*index] == '\'' && !single_quotes(data, tokens, input, index))
		return (0);
	return (1);
}