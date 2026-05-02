/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/01 16:24:40 by ethutin-         ###   ########.fr       */
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
		printf("key-> %s \n", view->key);
		printf("export-> %d \n", view->export);
		printf("====================\n");
		view = view->next;
	}
}

void	display_cmd(t_cmd *view)
{
	int	i;

	while (view)
	{
		i = -1;
		printf("============================\n");
		printf("cmd => {");
		while (view->cmd[++i])
		{
			printf("%s", view->cmd[i]);
			if (view->cmd[i + 1])
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

void	display_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		printf("%d: {%s - %d}\n", i, token->cmd, token->type);
		i++;
		token = token->next;
	}
}

void	display_token(t_token *view)
{
	printf("{");
	while (view)
	{
		printf("%s:%d", view->cmd, view->type);
		if (view->next)
			printf(", ");
		view = view->next;
	}
	printf("}\n");
}

	// //pour voir l'historique
	// HIST_ENTRY **history;
	// history = history_list();
	// int i = -1;
	// while (history[++i])
	//     printf("=> %s\n", history[i]->line);
//=======================================//

//signal(SIGQUIT, SIG_DFL);
volatile sig_atomic_t	g_signal;

void	init_env(t_data *data, char **env)
{
	t_env	*new;
	int		i;

	i = -1;
	new = NULL;
	if (make_built_env(data, new, env))
		return ;
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
	//display_env(data->t_env);
	main_reading(data, "pastishell$ ");
	return (0);
}
