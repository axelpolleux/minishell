/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:01:08 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/20 10:04:27 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token	*new;
	int		i;

	if (input[*index] != 34)
		return ;
	i = 1;
	while (input[*index + i] && input[*index + i] != 34)
		i++;
	if (!input[*index + i])
	{
		printf("Ferme tes quotes espece de fada !\n");
		exit(0);
	}
	new = token_new(input, index + 1, i - 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
}

void	single_quotes(t_data *data, t_token **tokens, char *input, int *index)
{
	t_token		*new;
	int			i;

	if (input[*index] != '\'')
		return ;
	i = 1;
	while (input[*index + i] && input[*index + i] != '\'')
		i++;
	if (!input[*index + i])
		data_malloc_error(data);
	new = token_new(input, index + 1, i - 1, WORD);
	if (!new)
		data_malloc_error(data);
	ft_token_add_back(tokens, new);
	(*index) += (i + 1);
}
