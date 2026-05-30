/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:52:20 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/26 17:27:00 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_error(t_data *data, int output)
{
	int	tmp;

	if (output == -2)
		data_malloc_error(data);
	tmp = output;
	free_data(data);
	exit(tmp);
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

void	opendir_error(t_data *data, char *error)
{
	ft_putstr_fd("minichevre: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(" : is a directory\n", 2);
	data->exit = 126;
}

void	error_cnf(t_data *data, char *error)
{
	ft_putstr_fd("enter_error_cnf", 1);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit = 127;
}
