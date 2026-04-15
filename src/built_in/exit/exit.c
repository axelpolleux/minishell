/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:31:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/15 14:32:41 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_atoi(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		res = *str * 10 + (*str - '0');
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str || (res > LONG_MAX && sign == 1)
		|| ((res - 1) > LONG_MAX && (sign == -1)))
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
	out = exit_atoi(cmd[1]);
	if (out == -1)
		error_exit(cmd[1]);
	arg = nb_arg(cmd);
	if (arg > 2)
	{
		error_perror(EXT_ARG, C_ERROR, NF);
		return ;
	}
	if (arg == 1)
	{
		free_data(data);
		exit(data->exit);
	}
	free_data(data);
	exit(out);
}
