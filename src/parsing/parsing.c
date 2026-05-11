/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/11 15:23:21 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_tokens(t_token *token)
{
	t_token	*tokens;

	tokens = token;
	while (tokens)
	{
		printf("[%s]", tokens->cmd);
		tokens = tokens->next;
	}
	printf("\n");
}

int main_parser(t_data *data)
{
	if (data->token)
	{
		free_token(data->token);
		data->token = NULL;
	}
	data->token = tokeniser(data, data->line);
	if (!data->token)
		return (EXIT_FAILURE);
	display_tokens(data->token);
	// if (data->cmd)
	// {
	// 	free_cmd(data->cmd);
	// 	data->cmd = NULL;
	// }
	return (EXIT_SUCCESS);
}
