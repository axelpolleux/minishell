/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/15 16:23:06 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	if (line && *line && !full_void(line))
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

	line = main_reading("pastishell$ ");
	free(line);
	return (1);
}
