/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:54:02 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/30 10:33:37 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char *str, char c)
{
	int	count;
	int	trigger;

	count = 0;
	trigger = 0;
	while (*str)
	{
		if ((*str != c) && (trigger == 0))
		{
			trigger = 1;
			count++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (count);
}

static void	*ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static char	**fill_split(char const *s, char c, char **res)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len)
		{
			res[i] = ft_substr(s, 0, len);
			if (!res[i++])
			{
				ft_free(res);
				return (0);
			}
			s += len;
		}
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	**final_res;

	if (!s)
		return (NULL);
	res = ft_calloc(count_word((char *)s, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	final_res = fill_split(s, c, res);
	return (final_res);
}
