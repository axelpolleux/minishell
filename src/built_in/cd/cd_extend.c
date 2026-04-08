/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:23:45 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/08 13:55:54 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_chdir(char *path, char *new_pwd, size_t size)
{
	if (chdir(path) == -1 || !getcwd(new_pwd, size))
	{
		error_exit (CD_ER, C_ERROR, NF);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
