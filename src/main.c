/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/30 17:51:55 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=======a degager a la fin==========//
void	display_env(t_env *view)
{
	while (view)
	{
		printf("->%s \n", view->var);
		view = view->next;
	}
}

void	display_token(t_token *view)
{
	printf("{");
	while (view)
	{
		printf("%s", view->cmd);
		if (view->next)
			printf(", ");
		view = view->next;
	}
	printf("}\n");
}
void display_cmd(t_cmd *view)
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

	// HIST_ENTRY **history;
	// history = history_list();
	// int i = -1;
	// while (history[++i])
    //     printf("=> %s\n", history[i]->line);

//=======================================//

void reset(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->t_env)
    	free_env(data->t_env);
    if (data->cmd)
		free_cmd(data->cmd);
}


void get_env(t_data *data, char **env)
{
	t_env *new;
    int i;

	i = -1;
    while (env[++i])
    {
        new = new_env(ft_strdup(env[i]));
        if (!new)
            data_malloc_error(data);
        add_to_bottom(&data->t_env, new);
    }
}
int	exit_shell(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	if (line && *line)
		add_history(line);
	if (!strcmp(line, "exit")) // a ameliorer pour les space
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
    t_data *data;

    data = init_data(ac, av, env);
	data->built_in = init_built();
	if (!data->built_in)
		data_malloc_error(data);
    get_env(data, env);
    while (1)
    {
        data->line = readline("minishell> ");
		if (exit_shell(data->line))
			break ;
		add_history(data->line);
		tokenization(data);
        exec(data);
        //reset(data); pas bessoin
    }
    rl_clear_history();
    free_data(data);
    return (0);
}

 // if (!tokenization(data))//   !parse(data)
 // {
 //     reset(data);
 //     continue;
 // }

