/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:13:01 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/31 20:13:30 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_end(t_data *data, int count)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count)
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(data->pid[i], &status, 0) == -1)
			wait_error(data);
		signal(SIGINT, handle_signal);
		if (WIFEXITED(status))
			data->exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit = 128 + WTERMSIG(status);
	}
	free(data->pid);
	data->pid = NULL;
}
