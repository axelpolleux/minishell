/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:06:25 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/20 17:42:53 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include"exec.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str_des;
	unsigned char	*str_src;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	str_des = dest;
	str_src = (unsigned char *)src;
	while (i < n)
	{
		str_des[i] = str_src[i];
		i++;
	}
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*cop;
	char			*verif_dup;
	size_t			len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		verif_dup = ft_strdup("");
		return (verif_dup);
	}
	if (len > len_s - start)
		len = len_s - start;
	cop = malloc((len + 1) * sizeof(char));
	if (!cop)
		return (NULL);
	cop = ft_memcpy(cop, s + start, len);
	cop[len] = '\0';
	return (cop);
}

char	*ft_strdup(char *src)
{
	char	*duplicate;
	int		i;

	i = 0;
	while (src[i])
		i++;
	duplicate = (char *)malloc((i + 1) * sizeof(char));
	if (!duplicate)
		return (0);
	i = 0;
	while (src[i])
	{
		duplicate[i] = src[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len_s1;
	size_t		len_s2;
	char		*concat;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	concat = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!concat)
		return (NULL);
	ft_memcpy(concat, s1, len_s1);
	ft_memcpy(concat + len_s1, s2, len_s2 + 1);
	return (concat);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	cp;
	unsigned char	*start;
	size_t			i;

	i = 0;
	cp = c;
	start = s;
	while (i < n)
	{
		*start = cp;
		start++;
		i++;
	}
	return (s);
}
