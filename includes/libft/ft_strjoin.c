/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:53:39 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 10:19:46 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		s1len;
	int		s2len;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1len + s2len) + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, s1, (s1len + 1));
	ft_strlcat(res, s2, (s1len + s2len + 1));
	return (res);
}
