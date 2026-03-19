/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:20:20 by ethutin-          #+#    #+#             */
/*   Updated: 2025/10/30 17:33:58 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putstr(char *str, int *len)
{
	if (str == NULL)
		ft_putstr("(null)", len);
	else
	{
		while (*str)
			ft_putchar(*str++, len);
	}
	return ;
}
