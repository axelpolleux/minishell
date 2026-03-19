/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:02:11 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/12 11:32:51 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*free_arr(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	word_size(char *str, char charset)
{
	int	i;

	i = 0;
	while (*str && *str != charset)
	{
		i++;
		str++;
	}
	return (i);
}

static int	total_word(char *str, char charset)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str != charset)
		{
			str += word_size(str, charset);
			i++;
		}
		else
			str++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nb_word;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	nb_word = total_word((char *)s, c);
	tab = malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	tab[nb_word] = 0;
	while (*s)
	{
		if (*s != c)
		{
			tab[i] = ft_substr((char *)s, 0, word_size((char *)s, c));
			if (!tab[i++])
				return (free_arr(tab));
			s += word_size((char *)s, c);
		}
		else
			s++;
	}
	return (tab);
}
