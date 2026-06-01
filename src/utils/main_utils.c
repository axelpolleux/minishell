/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:41:20 by apolleux          #+#    #+#             */
/*   Updated: 2026/06/01 18:28:56 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	g_signal_init(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
}

void	g_signal_while(t_data *data)
{
	g_signal = 0;
	data->line = readline(TITLE);
	if (g_signal == SIGINT)
		data->exit = 130;
}

void	check_exit(t_data *data)
{
	if (data->exit != 0)
		parser_error(data, data->exit);
	reset_read(data);
}
