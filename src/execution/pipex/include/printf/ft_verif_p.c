/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:37:29 by ethutin-          #+#    #+#             */
/*   Updated: 2025/10/31 08:24:31 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_putnbr_base_p(size_t nbr, char *base, int *len)
{
	if (nbr >= ft_strlen(base))
		ft_putnbr_base_p(nbr / ft_strlen(base), base, len);
	ft_putchar(base[nbr % ft_strlen(base)], len);
}

void	ft_verif_p(size_t nbr, char *base, int *len)
{
	if (nbr == 0)
		ft_putstr("(nil)", len);
	else
	{
		ft_putstr("0x", len);
		ft_putnbr_base_p(nbr, base, len);
	}
}
