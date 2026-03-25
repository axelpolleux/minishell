/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/25 21:12:47 by apolleux         ###   ########.fr       */
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
	while (view)
	{
		printf("============================\n");
		printf("token => {%s}\n", view->content);
		view = view->next;
	}
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

//=======================================//

// void	get_new(int i, char *line, char **env, t_data *data)
// {
// 	t_env	*new;

// 	while (env[i])
// 	{
// 		line = ft_strdup(env[i]);
// 		if (!line)
// 			data_malloc_error(data);
// 		new = new_env(line);
// 		if (!new)
// 		{
// 			free(line);
// 			data_malloc_error(data);
// 		}
// 		add_to_bottom(&data->env, new);
// 		i++;
// 	}
// }

// int	get_env(t_data *data, char **env)
// {
// 	t_env	*tmp;
// 	char	*line;

// 	if (!env || !(*env)) // a reconstruire ?    oui imperativement
// 	{
// 		//make_env(t_data *data);
// 		free_data(data);
// 		exit (0);
// 	}
// 	line = ft_strdup(env[0]);
// 	if (!line)
// 		data_malloc_error(data);
// 	tmp = new_env(line);
// 	if (!tmp)
// 	{
// 		free(line);
// 		data_malloc_error(data);
// 	}
// 	data->env = tmp;
// 	get_new(1, line, env, data);
// 	return (1);
// }

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

int	main(void)
{
	char	*line;
	char	**word;
	int		i;

	while (1)
	{
		line = readline("mimishell> ");
		if (exit_shell(line))
			break ;
		word = token_slpit(line);
		i = -1;
		while (word[++i])
			printf("%d -> {%s}\n", i + 1, word[i]);
		free_arr(word);
		free(line);
	}
	rl_clear_history();
	return (0);
}
