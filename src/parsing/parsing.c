/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/12 19:05:06 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_cmd(t_cmd *commands)
{
	int	i;

	(void)i;
	printf(">===========<\ncommand: [%s]", commands->command);
	i = 0;
	while (commands->args[i])
	{
		printf("[%s]", commands->args[i]);
		i++;
	}
	printf("\ncmd_path: [%s]\nfull_cmd: [%s]", commands->cmd_path, commands->full_cmd);
	i = 0;
	while (commands->input[i])
	{
		printf("[%s]", commands->input[i]);
		i++;
	}
	i = 0;
	while (commands->output[i])
	{
		printf("[%s]", commands->output[i]);
		i++;
	}
	commands = commands->next;
}

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

int	main_parser(t_data *data)
{
	if (data->token)
	{
		free_token(data->token);
		data->token = NULL;
	}
	data->token = tokeniser(data, data->line);
	if (!data->token)
		return (EXIT_FAILURE);
	data->cmd = parse_commands(data->token);
	return (EXIT_SUCCESS);
}
