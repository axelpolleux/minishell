/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/30 14:37:23 by ethutin-         ###   ########.fr       */
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

void	get_new(int i, char *line, char **env, t_data *data)
{
	t_env	*new;

	while (env[i])
	{
		line = ft_strdup(env[i]);
		if (!line)
			data_malloc_error(data);
		new = new_env(line);
		if (!new)
		{
			free(line);
			data_malloc_error(data);
		}
		add_to_bottom(&data->t_env, new);
		i++;
	}
}

int	get_env(t_data *data, char **env)
{
	t_env	*tmp;
	char	*line;

	if (!env || !(*env)) // a reconstruire ?    oui imperativement
	{
		//make_env(t_data *data); biens biens plus tard
		free_data(data);
		exit (0);
	}
	line = ft_strdup(env[0]);
	if (!line)
		data_malloc_error(data);
	tmp = new_env(line);
	if (!tmp)
	{
		free(line);
		data_malloc_error(data);
	}
	data->t_env = tmp;
	get_new(1, line, env, data);
	return (1);
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
	if (!strcmp(line, "exit"))
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = init_data(ac, av, env);
	if (pipe(data->fd_storage) == -1)
		return (-1);
	get_env(data, env);
	//export_central(data);
	//display_env(data->env);
	while (1)
	{
		data->line = readline("mimishell> ");
		if (exit_shell(data->line))
			break ;
		tokenization(data);
		//exec(data);
	}
	rl_clear_history();
	free_data(data);
	return (0);
}
