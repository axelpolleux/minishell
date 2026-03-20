/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:53:33 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/20 17:43:01 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include"exec.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && str1[i] && (i < n - 1))
		i++;
	return (str1[i] - str2[i]);
}

void	closes(int fd, int *fd_storage)
{
	if (fd >= 0)
		close(fd);
	if (fd_storage)
	{
		if (fd_storage[0] >= 0)
			close(fd_storage[0]);
		if (fd_storage[1] >= 0)
			close(fd_storage[1]);
	}
}

int	srch_cmd(char *s, char c)
{
	while (*s && *s != '\0')
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mal;
	size_t	aloc;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	aloc = nmemb * size;
	if (aloc == 0 || aloc / nmemb != size)
		return (malloc(0));
	mal = malloc(nmemb * size);
	if (!mal)
		return (NULL);
	ft_memset(mal, 0, nmemb * size);
	return (mal);
}
