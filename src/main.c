/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/29 16:06:47 by apolleux         ###   ########.fr       */
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
	main_reading(data, "pastishell$ ");
	exec(data);
	return (0);
}
