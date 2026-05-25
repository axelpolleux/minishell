/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/25 13:21:59 by ethutin-         ###   ########.fr       */
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
			reset_read(data);
			continue ;
		}
		exec(data);
		free(data->line);
	}
	free_data(data);
}


void	init_env(t_data *data, char **env, int i)
{
	t_env	*new;
	char	*new_var;
	char	*new_arg;
	char	*new_key;

	new = NULL;
	new_var = NULL;
	new_arg = NULL;
	new_key = NULL;
	if (make_built_env(data, new, env))
		return ;
	while (env[++i])
	{
		data->line_env = env[i];
		if (init_champ_env(data, &new_var, &new_arg, &new_key))
			init_env_fail(data, new_var, new_arg, new_key);
		new = new_env(new_var, new_arg, new_key, 1);
		if (!new)
			init_env_fail(data, new_var, new_arg, new_key);
		add_to_bottom_env (&data->t_env, new);
	}
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