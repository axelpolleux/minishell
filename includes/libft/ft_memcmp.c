/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:08:10 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 17:59:08 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!n || (!s1 && !s2))
		return (0);
	i = 0;
	n--;
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && n--)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
