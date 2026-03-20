/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_e.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:33:33 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/20 13:50:13 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*verif_read_line(ssize_t r, char *line, char **buf_ptr)
{
	if (r < 0)
	{
		if (line)
			free(line);
		if (buf_ptr && *buf_ptr)
		{
			free(*buf_ptr);
			*buf_ptr = NULL;
		}
		return (NULL);
	}
	if (buf_ptr && *buf_ptr)
	{
		free(*buf_ptr);
		*buf_ptr = NULL;
	}
	if (line && *line)
		return (line);
	if (line)
		free(line);
	return (NULL);
}

char	*line_add(char const *s1, char const *s2, size_t size)
{
	size_t	len_s1;
	size_t	i;
	char	*concat;

	i = 0;
	if (s1 && s2)
		len_s1 = ft_strlen(s1);
	else
		len_s1 = 0;
	concat = malloc((len_s1 + size + 1) * sizeof(char));
	if (!concat)
		return (NULL);
	while (s1 && *s1)
		concat[i++] = *(s1++);
	while (*s2 && (i - len_s1) < size)
		concat[i++] = *(s2++);
	concat[i] = 0;
	return (concat);
}

char	*read_line(int fd, char **buffer_ptr, char *line, size_t i)
{
	char	*buffer;
	ssize_t	r;

	buffer = *buffer_ptr;
	while (1)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buffer[r] = '\0';
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
			free_line(&line, line_add(line, buffer, i + 1));
		else
			free_line(&line, line_add(line, buffer, i));
		if (buffer[i] == '\n')
		{
			buffer_left(buffer, i + 1);
			return (line);
		}
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
	}
	return (verif_read_line(r, line, buffer_ptr));
}

int	init_buff(char **buffer)
{
	if (!*buffer)
	{
		*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!*buffer)
			return (0);
		(*buffer)[0] = '\0';
	}
	return (1);
}

char	*get_next_line_e(int fd, size_t i)
{
	static char	*buffer;
	char		*line;

	if (fd == -1)
		clean_buff(buffer);
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1023)
		return (NULL);
	if (!init_buff(&buffer))
		return (NULL);
	line = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		line = line_add(NULL, buffer, i + 1);
		buffer_left(buffer, i + 1);
		return (line);
	}
	if (buffer[0])
	{
		free_line(&line, line_add(line, buffer, ft_strlen(buffer)));
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
	}
	return (read_line(fd, &buffer, line, 0));
}
