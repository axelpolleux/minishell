/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:31:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 18:08:03 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_atoi(const char *str, int sign, long res)
{
	sign = 1;
	res = 0;
	if (!str)
		return (-1);
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (-1);
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str)
		return (-1);
	return ((int)((res * sign) % 256));
}

void	exec_exit(t_data *data, t_cmd *g_cmd, char **cmd)
{
	int		out;
	int		arg;

	if (g_cmd->output >= 0)
	{
		dup2(data->last_fd, 1);
		close (data->last_fd);
	}
	arg = nb_arg(cmd);
	if (arg > 1)
	{
		out = exit_atoi(cmd[1], 1, 0);
		if (out == -1)
			error_exit(data, cmd[1]);
	}
	if (arg > 2)
	{
		error_perror(EXT_ARG, P_ERROR, 2);
		return ;
	}
	else
		out = data->exit;
	printf("exit\n");
	free_data(data);
	exit(out);
}
