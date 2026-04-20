/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:18:18 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 17:55:02 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*str1;
	unsigned char		*str2;
	size_t				i;

	str1 = src;
	str2 = dest;
	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	return ((void *)str2);
}
