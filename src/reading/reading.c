/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:04:56 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/05 18:44:17 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	main_reading(t_data *data, char *title)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		g_signal = 0;
		data->line = readline(title);
		if (!data->line)
		{
			free_data(data);
			printf("exit\n");
			exit(0);
		}
		if (data->line && *(data->line) && !full_void(data->line))
			add_history(data->line);
		if (main_parser(data))
		{
			free(data->line);
			continue ;
		}
		exec(data);
		free(data->line);
		// if (data->exit != 0)
		// 	exec_fail(data);
	}
	free_data(data);
}
