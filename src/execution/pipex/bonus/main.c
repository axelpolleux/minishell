/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/12 11:32:51 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (ac < 5)
		ac_error ();
	data = init_data(ac);
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		data->doc = 1;
		data->start = 3;
		data->limit = av[2];
	}
	else
		data->start = 2;
	data->pid = ft_calloc(sizeof(pid_t), data->ac - data->start - 1);
	if (!data->pid)
		data_malloc_error(data);
	process_manage(data, env, av);
	return (0);
}
