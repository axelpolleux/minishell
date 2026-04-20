/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:25:04 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/21 18:22:24 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	if (s[i] == (unsigned char)c)
		return ((char *)(s + i));
	while (i--)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	}
	return (0);
}
