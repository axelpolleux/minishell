/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/07 16:16:24 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	display_cmd(t_cmd *view)
// {
// 	int	i;
//
// 	i = 0;
// 	while (view)
// 	{
// 		printf("============================\n");
// 		printf("cmd => ");
// 		while (view->cmd[i])
// 		{
// 			printf("[%s]", view->cmd[i]);
// 			if (view->next)
// 				printf(", ");
// 			i++;
// 		}
// 		printf("\n");
// 		printf("cmd_path => %s\n", view->cmd_path);
// 		printf("full_cmd => %s\n", view->full_cmd);
// 		printf("input => %d\n", view->input);
// 		printf("output => %d\n", view->output);
// 		view = view->next;
// 	}
// }

int	main(int ac, char **av, char **env)
{
	(void)env;
	t_data	*data;

	data = init_data(ac, av);
	data->built_in = init_built();
	if (!data->built_in)
		data_malloc_error(data);
	main_reading(data, "pastishell$ ");
	free_data(data);
	return (0);
}
