/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/31 14:00:15 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_data *data, char **word)
{
	int		i;
	t_token	*last;
	t_token	*new_node;

	i = 0;
	last = NULL;
	while (word[i])
	{
		new_node = new_token(last, word[i]);
		if (!new_node)
			data_malloc_error(data);
		if (!data->token)
			data->token = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
}

void	tokenization(t_data *data)
{
	char	**word;

	if (data->token)
	{
		free_token(data->token);
		data->token = NULL;
	}
	word = token_split(data->line);
	if (!word)
		data_malloc_error(data);
	create_token(data, word);
	//display_token(data->token);
	free_arr(word);
	free(data->line);
}
