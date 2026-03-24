/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/24 17:17:50 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display(t_token *view)
{
	int	i;

	i = 0;
	while (view)
	{
		printf("->%s \n", view->cmd);
		view = view->next;
	}
}


	// HIST_ENTRY **history;
	// history = history_list();
	// int i = -1;
	// while (history[++i])
    //     printf("=> %s\n", history[i]->line);

void	get_new(int i, char *line, char **env, t_data *data)
{
	t_st_env 	*new;

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
		add_to_bottom(&data->st_env, new);
		i++;
	}
}

int	get_env(t_data *data, char **env)
{
	t_st_env	*tmp;
	char		*line;

	if (!env || !(*env)) // a reconstruire ?
	{
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
	data->st_env = tmp;
	get_new(1, line, env, data);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = init_data(ac, av);
	get_env(data, env);
	while (1)
	{
		data->line = readline("mimishell> ");
		if (!data->line)
    	{
        	printf("exit\n");
        	break;
    	}
    	if (data->line && *data->line)
			add_history(data->line);
		if (!strcmp(data->line, "exit"))
		{
			printf("exit\n");
			break ;
		}
		tokenization(data);
		//exec(data);
   	 	free(data->line);
	}
	rl_clear_history();
	free_data(data);
	return (0);
}
	