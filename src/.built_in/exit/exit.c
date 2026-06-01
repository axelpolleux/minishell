/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:31:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/28 17:37:56 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_arg(t_data *data, char *str, int *out)
{
	long	res;

	res = exit_atoi(str, 1, 0);
	if (res == LONG_MAX)
		error_exit(data, str);
	*(out) = (int)(res % 256);
}

long	exit_atoi(const char *str, int sign, long res)
{
	sign = 1;
	res = 0;
	if (!str)
		return (LONG_MAX);
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (LONG_MAX);
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str)
		return (LONG_MAX);
	return (res * sign);
}

void	exec_exit(t_data *data, t_cmd *cmd, char **args)
{
	int	out;
	int	arg;

	if (cmd->output >= 0)
	{
		dup2(data->last_fd, 1);
		close(data->last_fd);
	}
	arg = nb_arg(args);
	if (arg > 1)
		exit_arg(data, args[1], &out);
	else
		out = data->exit;
	if (arg > 2)
	{
		error_perror(EXT_ARG, P_ERROR, 2);
		data->exit = 2;
		return ;
	}
	data->exit = out;
	if (cmd->next || cmd->prev)
		return ;
	printf("exit\n");
	free_data(data);
	exit(out);
}
