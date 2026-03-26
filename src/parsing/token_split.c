/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:39:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/26 14:27:24 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	get_len(int i, int count, char *str)
{
	char	sep;

	while (str[i])
	{
		while (space(str[i]))
			i++;
		if (!str[i])
			break ;
		count++;
		while (str[i] && !space(str[i]))
		{
			if (quote(str[i]))
			{
				sep = str[i++];
				while (str[i] && str[i] != sep)
					i++;
				if (str[i])
					i++;
			}
			else
				i++;
		}
	}
	return (count);
}

char	*get_word(char *s, int *i)
{
	char	*line;
	char	quote;
	int		start;

	while (space(s[*i]))
		(*i)++;
	if (!s[*i])
		return (NULL);
	start = *i;
	while (s[*i] && !space(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			quote = s[(*i)++];
			while (s[*i] && s[*i] != quote)
				(*i)++;
			if (s[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	line = ft_substr(s, start, *i - start);
	return (line);
}

char	**token_split(char *str)
{
	char	**word;
	int		i;
	int		j;
	int		k;

	if (!str)
		return (NULL);
	i = 0;
	j = get_len(0, 0, str);
	word = ft_calloc(sizeof(char *), j + 1);
	if (!word)
		return (NULL);
	k = -1;
	while (++k < j)
	{
		word[k] = get_word(str, &i);
		if (!word[k])
			return (NULL);
	}
	word[k] = NULL;
	return (word);
}
