/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:10:39 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/29 10:19:39 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	newstr = (char *)malloc((i + 1) * (sizeof(char)));
	if (!newstr)
		return (NULL);
	while (s[j])
	{
		newstr[j] = s[j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}
