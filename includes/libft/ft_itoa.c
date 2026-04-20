/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:54:08 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 10:18:57 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_len(long n)
{
	int	tlen;

	tlen = 0;
	if (n < 0)
	{
		tlen++;
		n *= (-1);
	}
	if (n == 0)
		tlen++;
	while (n)
	{
		n /= 10;
		tlen++;
	}
	return (tlen);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;
	long			nbr;

	nbr = (long int)n;
	len = calc_len(nbr);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	res[len--] = '\0';
	if (nbr == 0)
		res[len] = '0';
	if (nbr < 0)
	{
		res[0] = '-';
		nbr *= (-1);
	}
	while (nbr)
	{
		res[len--] = ((nbr % 10) + 48);
		nbr /= 10;
	}
	return (res);
}
