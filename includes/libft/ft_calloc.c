/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:10:42 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 18:05:59 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (0);
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	ft_bzero(res, size * nmemb);
	return (res);
}
