/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:53:49 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/30 10:31:05 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	slen;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (*s1 == '\0')
	{
		res = ft_calloc(1, sizeof(char));
		return (res);
	}
	slen = ft_strlen(s1);
	if (slen <= 0)
		return (0);
	while (ft_strchr(set, s1[slen - 1]))
		slen--;
	res = ft_substr(s1, 0, slen);
	return (res);
}
