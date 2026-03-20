/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/20 16:47:06 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	// t_data	*data;
	// t_node	*node;
	(void)av;
	(void)env;

	if (ac < 2)
		ac_error ();
	// node = init_node(av);
	// data = init_data(ac);
	// data->start = 2;
	// data->pid = ft_calloc(sizeof(pid_t), data->executable);
	// if (!data->pid)
	// 	data_malloc_error(data);
	// process_manage(data, node, env, av);
	return (0);
}
