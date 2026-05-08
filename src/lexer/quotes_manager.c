/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:01:08 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/08 18:50:42 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		i;
	int	start;
	if (input[*index] != '\"')
		return (EXIT_SUCCESS);
	i = 1;
	while (input[*index + i] && input[*index + i] != 34)
		i++;
	if (!input[*index + i])
		return (error_quote());
	start = *index;
	new = token_new(input, &start, i + 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
	return (EXIT_SUCCESS);
}




int	single_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		i;
	int		start;

	if (input[*index] != '\'')
		return (EXIT_SUCCESS);
	i = 1;
	while (input[*index + i] && input[*index + i] != '\'')
		i++;
	if (!input[*index + i])
		return(error_quote());
	start = *index;
	new = token_new(input, &start, i + 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
	return (EXIT_SUCCESS);
}
