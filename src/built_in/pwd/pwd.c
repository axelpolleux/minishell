/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:14:40 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/15 13:54:32 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_data * data)
{
	char	*pwd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd("\n", 1);
		free(tmp);
		return (EXIT_SUCCESS);
	}
	pwd = get_arg_env(data, PWD);
	if (!pwd)
	{
		error_perror(PWD_ER, C_ERROR, NF);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
