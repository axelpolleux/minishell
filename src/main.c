/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/29 15:34:49 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_read(t_data *data)
{
	free_token(data->token);
	data->token = NULL;
	free_cmd(data->cmd);
	data->cmd = NULL;
	free(data->line);
	data->line = NULL;
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
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	data->cmd = parsing_commands(data, data->token);
	if (!data->cmd)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	main_reading(t_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	rl_event_hook = rl_event;
	while (1)
	{
		g_signal = 0;
		data->line = readline(TITLE);
		if (g_signal == SIGINT)
			data->exit = 130;
		if (!data->line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (!data->line[0])
		{
			free(data->line);
			continue ;
		}
		if (data->line && *(data->line) && !full_void(data->line))
			add_history(data->line);
		if (main_parser(data))
		{
			if (data->exit != 0)
				parser_error(data, data->exit);
			reset_read(data);
			continue ;
		}
		exec(data);
		reset_read(data);
	}
	free_data(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = init_data(ac, av);
	data->built_in = init_built();
	if (!data->built_in)
		data_malloc_error(data);
	init_env(data, env, -1);
	main_reading(data);
	return (EXIT_SUCCESS);
}
