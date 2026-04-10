/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:14:40 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/08 16:46:28 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error_exit (PWD_ER, C_ERROR, NF);
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free (pwd);
	return (EXIT_SUCCESS);
}
