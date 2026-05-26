/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/26 16:50:43 by apolleux         ###   ########.fr       */
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
	if (data->path)
	{
		free_arr(data->path);
		data->path = NULL;
	}
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
}

int	main_parser(t_data *data)
{
	if (data->token)
	{
		free_token(data->token);
		data->token = NULL;
	}
	data->token = tokeniser(data, data->line);
	// display_tokens(data->token);
	if (!data->token)
		return (EXIT_FAILURE);
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	data->cmd = parsing_commands(data->token);
	if (!data->cmd)
		return (EXIT_FAILURE);
	// display_cmd(data->cmd);
	return (EXIT_SUCCESS);
}

void	main_reading(t_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		g_signal = 0;
		data->line = readline(TITLE);
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
	//display_env(data->t_env);
	main_reading(data);
	return (EXIT_SUCCESS);
}
// leak a env i
//  comportement heredoc erratique    
// les erreur du init_cmd sont incomplete
// les redir parte en couille      > test non creation de test
// oublie pas en sortie de program la sorti 13

/*
bash
echo dfghjkl wdwd wdqwdwqdwdwq dwqd d | grep d
dfghjkl wdwd wdqwdwqdwdwq dwqd d


pastishell$ echo dfghjkl wdwd wdqwdwqdwdwq dwqd d | grep d
============================
cmd => {echo, dfghjkl, wdwd, wdqwdwqdwdwq, dwqd, d, |, grep, d}
cmd_path => (null)
full_cmd => (null)
input => -1
output => -1
dfghjkl wdwd wdqwdwqdwdwq dwqd d | grep d
*/



/*
gestion d'erreur dans main parser qui ne fait que un reset et n'arrete pas le propgramme]
*/