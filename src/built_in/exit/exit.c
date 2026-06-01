/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:31:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/01 17:06:34 by apolleux         ###   ########.fr       */
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

static long	parse_digits(const char *str)
{
	long	res;

	res = 0;
	while (ft_isdigit(*str))
	{
		if (res > (INT_MAX - (*str - '0')) / 10)
			return (LONG_MAX);
		res = res * 10 + (*str - '0');
		str++;
	}
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str)
		return (LONG_MAX);
	return (res);
}

long	exit_atoi(const char *str, int sign, long res)
{
	sign = 1;
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
	res = parse_digits(str);
	if (res == LONG_MAX)
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
