/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/22 17:47:48 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!data->token)
		return ;
	display_tokens(data->token);
	data->cmd = commander(data->token);
	if (!data->cmd)
		return ;
	display_cmd(data->cmd);
}
