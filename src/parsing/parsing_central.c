/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_central.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:39:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/25 21:04:52 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*get_word(char *s, int *i)
{
	int		start;
	char	quote;

	while (is_space(s[*i]))
		(*i)++;
	if (!s[*i])
		return (NULL);
	start = *i;
	while (s[*i] && !is_space(s[*i]))
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
	return (ft_substr(s, start, *i - start));
}

char	**token_slpit(char *str)
{
	char	**word;
	char	*tok;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	word = ft_calloc(sizeof(char *), 100);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (1)
	{
		tok = get_word(str, &i);
		if (!tok)
			break ;
		j++;
	}
	word[j] = NULL;
	return (word);
}
