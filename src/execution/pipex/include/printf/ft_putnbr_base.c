/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:23:45 by ethutin-          #+#    #+#             */
/*   Updated: 2025/10/30 18:14:48 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putnbr_base(size_t nbr, char *base, int *len)
{
	if (nbr >= ft_strlen(base))
		ft_putnbr_base(nbr / ft_strlen(base), base, len);
	ft_putchar(base[nbr % ft_strlen(base)], len);
}
