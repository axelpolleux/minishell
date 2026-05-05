/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:52:20 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 17:53:39 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_fail(t_data *data)
{
	int	exit_exec;

	exit_exec = data->exit;
	free_data(data);
	exit (exit_exec);
}

void	init_env_fail(t_data *data, char *new_env, char *new_arg, char *new_key)
{
	if (new_env)
		free(new_env);
	if (new_arg)
		free(new_arg);
	if (new_key)
		free(new_key);
	data_malloc_error(data);
}

void	init_env_fail_n(char *new_env, char *new_arg, char *new_key)
{
	if (new_env)
		free(new_env);
	if (new_arg)
		free(new_arg);
	if (new_key)
		free(new_key);
}

// hugo ma prensenter une de ces gestion de signaux, je la mais la pour voire
// void	error_signal(int signal)
// {
// 	char	*str;
// 	int		fd;

// 	str = ft_itoa(signal + 128);
// 	fd = open("/tmp/.$?", O_CREAT | O_TRUNC | O_WRONLY, 0664);
// 	ft_putstr_fd(str, fd);
// 	free(str);
// 	close(fd);
// }

// void	error_message(char *arg, char *mes_err)
// {
// 	if (mes_err)
// 	{
// 		ft_putstr_fd(arg, 2);
// 		ft_putstr_fd(" : ", 2);
// 		ft_putendl_fd(mes_err, 2);
// 	}
// }
