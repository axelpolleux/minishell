/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_e.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:01:29 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/20 13:50:19 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_line(char **line, char *new_line)
{
	if (*line && *line != new_line)
		free (*line);
	*line = new_line;
}

void	buffer_left(char *buffer, size_t start)
{
	size_t	left;
	size_t	j;

	left = ft_strlen(buffer + start);
	j = 0;
	while (j <= left)
	{
		buffer[j] = buffer[start + j];
		j++;
	}
}

char	*clean_buff(char *buffer)
{
	free(buffer);
	buffer = NULL;
	return (NULL);
}
