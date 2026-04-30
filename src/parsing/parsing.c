/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/22 15:38:44 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_cmd(t_cmd *commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands)
	{
		printf("No %d\ncmd: ", i);
		i++;
		j = 0;
		while (commands->cmd[j])
		{
			printf("[%s]", commands->cmd[j]);
			j++;
		}
		printf("\n");
		printf("Path: %s\n", commands->cmd_path);
		printf("Full cmd: %s\n", commands->full_cmd);
		printf("Input: %d\n", commands->input);
		printf("Output: %d\n", commands->output);
		commands = commands->next;
	}
}

void	main_parser(t_data *data)
{
	if (data->token)
	{
		free_token(data->token);
		data->token = NULL;
	}
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	data->token = tokeniser(data, data->line);
	data->cmd = parse_commands(data->token);
	if (!data->cmd)
		return ;
	display_cmd(data->cmd);
}
