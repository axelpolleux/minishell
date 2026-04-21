/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/20 17:50:03 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=======a degager a la fin==========//
void	display_env(t_env *view)
{
	while (view)
	{
		printf("var-> %s \n", view->var);
		printf("arg-> %s \n", view->arg);
		printf("export-> %d \n", view->export);
		printf("====================\n");
		view = view->next;
	}
}

void	display_cmd(t_cmd *view)
{
	int	i;

	i = 0;
	while (view)
	{
		printf("============================\n");
		printf("{");
		while (view->cmd[i])
		{
			printf("cmd => %s", view->cmd[i]);
			if (view->next)
				printf(", ");
		}
		printf("}\n");
		printf("cmd_path => %s\n", view->cmd_path);
		printf("full_cmd => %s\n", view->full_cmd);
		printf("input => %d\n", view->input);
		printf("output => %d\n", view->output);
		view = view->next;
	}
}
	// //pour voir l'historique
	// HIST_ENTRY **history;
	// history = history_list();
	// int i = -1;
	// while (history[++i])
	//     printf("=> %s\n", history[i]->line);
//=======================================//

// void reset(t_data *data)
// {
// 	if (data->line)
// 		free(data->line);
// 	if (data->t_env)
//     	free_env(data->t_env);
//     if (data->cmd)
// 		free_cmd(data->cmd);
// }

void	init_env(t_data *data, char **env)
{
	t_env	*new;
	int		i;

	i = -1;
	if (!env || !(*env))
	{
		free_data(data);
		exit(0);
	}
	while (env[++i])
	{
		new = new_env(ft_strdup(env[i]), 1);
		if (!new)
			data_malloc_error(data);
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
	init_env(data, env);
	main_reading(data, "pastishell$ ");
	return (1);
}
//PAS DE PANIQUE LE EXIT IL VIENDRA DES BUILT IN
