/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/26 17:51:47 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=======a degager a la fin==========//
void	display_env(t_env *view)
{
	int	i;

	i = 0;
	while (view)
	{
		printf("->%s \n", view->var);
		view = view->next;
	}
}

void	display_token(t_token *view)
{
	int	i;

	i = 0;
	printf("{");
	while (view)
	{
		printf("\"%s\"", view->cmd);
		if (view->next)
			printf(", ");
		view = view->next;
	}
	printf("}\n");
}
// void display_cmd(t_token *view)
// {
// 	int	i;

// 	i = 0;
// 	while (view)
// 	{
// 		printf("============================\n");
// 		printf("token => {%s}\n", view->cmd);
// 		view = view->next;
// 	}
// }

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
		add_to_bottom(&data->env, new);
		i++;
	}
}

int	get_env(t_data *data, char **env)
{
	t_env	*tmp;
	char	*line;

	if (!env || !(*env)) // a reconstruire ?    oui imperativement
	{
		//make_env(t_data *data); bien bien plus tard
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
	data->env = tmp;
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

	data = init_data(ac, av);
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
		process_manage(data);
	}
	rl_clear_history();
	free_data(data);
	return (0);
}
