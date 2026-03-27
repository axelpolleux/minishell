/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:04:56 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/27 10:04:01 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/history.h>

#include "minishell.h"

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*main_reading(char *title)
{
	char	*line;
	char	*res;

	res = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		line = readline(title);
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		res = line;
		free(line);
	}
	clear_history();
	return (res);
}
