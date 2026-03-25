/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/25 16:49:35 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	creat_token(t_data *data, char **pipe_split)
// {
// 	t_token	*last;
// 	t_token	*new_node;
// 	char	**word;
// 	int		i;

// 	i = 0;
// 	last = NULL;
// 	while (pipe_split[i])
// 	{
// 		//token_split = ft_split(pipe_split[i], ' ');
// 		word = token_split(pipe_split[i]);
// 		if (!word)
// 			data_malloc_error(data);
// 		new_node = new_token(last, word, pipe_split[i]);
// 		if (!new_node)
// 			data_malloc_error(data);
// 		if (!data->token)
// 			data->token = new_node;
// 		else
// 			last->next = new_node;
// 		last = new_node;
// 		i++;
// 	}
// }

// void	tokenization(t_data *data)
// {
// 	char	**pipe_split;

// 	if (data->token)
// 	{
// 		free_token(data->token);
// 		data->token = NULL;
// 	}
// 	pipe_split = quote_split(data->line);
// 	if (!pipe_split)
// 		data_malloc_error(data);
// 	creat_token(data, pipe_split);
// 	display_token(data->token);
// 	free_arr(pipe_split);
// 	free(data->line);
// }
