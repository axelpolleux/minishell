/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:32:38 by apolleux          #+#    #+#             */
/*   Updated: 2026/06/01 23:35:34 by ethutin-         ###   ########.fr       */
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
