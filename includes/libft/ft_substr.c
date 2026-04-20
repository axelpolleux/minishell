/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:53:30 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 17:15:31 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	char			*res;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		res = (char *)ft_calloc(1, sizeof(char));
		if (!res)
			return (0);
		return (res);
	}
	if (len > (s_len - start))
		len = s_len - start;
	len++;
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (0);
	ft_strlcpy(res, s + start, len);
	return (res);
}
