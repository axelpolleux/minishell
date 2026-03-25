/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_central.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:39:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/25 18:22:19 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_operator(char c)
// {
// 	return (c == '|' || c == '<' || c == '>');
// }

// char	*get_word(char *s)
// {
// 	int     i;
// 	char    quote;

//     i = 0;
//     while (s[i])
//     {
// 	while (s[i]  == ' ' || c == '\t' || c == '\n')
// 		i++;
// 	if (!s[i])
// 		return (NULL);
// 	if (is_operator(s[*i]))
// 	{
// 		start = (*i)++;
// 		if ((s[start] == '>' && s[*i] == '>') ||
// 			(s[start] == '<' && s[*i] == '<'))
// 			(*i)++;
// 		return (substr(s, start, *i - start));
// 	}

// 	start = *i;
// 	while (s[*i] && !is_space(s[*i]) && !is_operator(s[*i]))
// 	{
// 		if (s[*i] == '\'' || s[*i] == '"')
// 		{
// 			quote = s[(*i)++];
// 			while (s[*i] && s[*i] != quote)
// 				(*i)++;
// 			if (s[*i])
// 				(*i)++;
// 		}
// 		else
// 			(*i)++;
// 	}
//     }
// 	return (substr(s, start, *i - start));
// }

// char	**token_slpit(char *s)
// {
// 	char	**tokens;
// 	char	*tok;
//     int     i;

//     i = 0;
// 	tokens = ft_calloc(sizeof(char *), 100); // pour test
// 	if (!tokens)
// 		return (NULL);
// 	while ((tok = get_word(s)))
// 	{
// 		tokens[j++] = tok;
// 	}
// 	tokens[j] = NULL;
// 	return (tokens);
// }



int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*get_word(char *s, int *i)
{
	int     start;
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
    int     j;

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
    // j = 0;
    // while (1)
    // {
    //     tok = get_word(str, &i);
    //     if (!tok)
    //         break ;
	// 	j++;
    // }
	return (word);
}
