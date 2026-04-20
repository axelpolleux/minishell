/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:04:03 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/28 14:23:42 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*str1;
	unsigned char		*str2;
	size_t				i;

	str1 = src;
	str2 = dest;
	if (!dest && !src)
		return (0);
	if (src < dest)
	{
		i = n - 1;
		while (i < n)
		{
			str2[i] = str1[i];
			i--;
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (str2);
}
