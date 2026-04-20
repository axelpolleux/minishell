/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:14:32 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 17:03:34 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;
	size_t	tofill;

	i = 0;
	slen = ft_strlen(src);
	if (size == 0)
		return (slen);
	dlen = ft_strlen(dst);
	if (dlen >= size)
		dlen = size;
	if (dlen == size)
		return (size + slen);
	tofill = size - dlen - 1;
	while (src[i] && tofill--)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
