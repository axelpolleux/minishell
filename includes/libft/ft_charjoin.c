/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:18:49 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/23 18:57:20 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char *str, char c)
{
	char	*new_line;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_line = ft_strjoin(str, tmp);
	free(str);
	if (!new_line)
		return (NULL);
	return (new_line);
}
