/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:52:20 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/24 16:04:09 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
