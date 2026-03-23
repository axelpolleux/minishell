/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/23 15:36:06 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display(t_st_env *view)
{
	int	i;

	i = 0;
	while (view)
	{
		printf("%s \n", view->var);
		view = view->next;
	}
}

int	get_env(t_data *data, char **env)
{
	t_st_env	*tmp;
	char		*line;
	int			i;

	if (!env || !(*env))
		return (0); // a reconstruire ?
	i = 0;
	line = ft_strdup(env[i]);
	if (!line)
		data_malloc_error(data);
	tmp = new_env(line);
	data->st_env = tmp;
	i++;
	while (env[i])
	{
		line = ft_strdup(env[i]);
		if (!line)
			data_malloc_error(data);
		add_to_bottom(&data->st_env, new_env(line));
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (ac < 2)
		ac_error ();
	data = init_data(ac, av);
	if (get_env(data, env))
	{
		free_data(data);
		return (0);
	}
	display(data->st_env);
	free_data(data);
	return (0);
}
