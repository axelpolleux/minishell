/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:32:38 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/31 21:35:53 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_for_exec(t_data *data)
{
	data->pid = ft_calloc(sizeof(pid_t), ft_lstsize_c(data->cmd));
	if (!data->pid)
		data_malloc_error(data);
	handle_exec_loop(data, ft_lstsize_c(data->cmd));
}
