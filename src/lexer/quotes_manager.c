/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:01:08 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/21 16:13:13 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		i;
	int		start;

	if (input[*index] != '\"')
		return ;
	i = 1;
	while (input[*index + i] && input[*index + i] != 34)
		i++;
	if (!input[*index + i])
		error_quote();
	start = *index + 1;
	new = token_new(input, &start, i - 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
}

void	single_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		i;
	int		start;

	if (input[*index] != '\'')
		return ;
	i = 1;
	while (input[*index + i] && input[*index + i] != '\'')
		i++;
	if (!input[*index + i])
		error_quote();
	start = *index + 1;
	new = token_new(input, &start, i - 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
}
