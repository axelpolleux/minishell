/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:54:16 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 18:14:39 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	unsigned int		rlen;
	char				*res;

	if (!s || !f)
		return (0);
	i = 0;
	rlen = ft_strlen(s);
	res = (char *)malloc((rlen + 1) * sizeof(char));
	if (!res)
		return (0);
	while (i < rlen)
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
