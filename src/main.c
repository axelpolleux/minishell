/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/01 16:49:51 by apolleux         ###   ########.fr       */
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

static void	exit_properly(t_data *data, int *exit)
{
	*exit = data->exit;
	free_data(data);
}

void	main_reading(t_data *data, int *exit)
{
	g_signal_init();
	while (1)
	{
		g_signal_while(data);
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
			check_exit(data);
			continue ;
		}
		exec(data);
		reset_read(data);
	}
	exit_properly(data, exit);
}

int	main(int ac, char **av, char **env)
{
	int			final_exit;
	t_data		*data;

	data = init_data(ac, av);
	data->built_in = init_built();
	if (!data->built_in)
		data_malloc_error(data);
	init_env(data, env, -1);
	main_reading(data, &final_exit);
	return (final_exit);
}
// gestion des signaux avec rl_done interdite