/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:09:53 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/20 18:34:55 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_parser(t_data *data)
{
	//=============TOKEN==============//
	if (data->token) //par pure parano
	{
		free_token(data->token);
		data->token = NULL;
	}
	data->token = tokeniser(data, data->line);
	display_token(data->token);
	//===============================//
	//
	// //=============CMD==============//
	// if (data->cmd) //par pure parano
	// {
	// 	free_cmd(data->cmd);
	// 	data->cmd = NULL;
	// }
	// data->cmd = init_cmd(data, data->token);
	// display_cmd(data->cmd);
	// //===============================//
}
