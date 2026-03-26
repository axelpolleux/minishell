/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_central.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:39:10 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/26 16:05:57 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char* get_word(char* s, int* i)
{
	int start;
	char quote;

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

char** token_split(char* str)
{
	char** word;
	char* tok;
	int i;
	int j;

	if (!str)
		return (NULL);
	word = ft_calloc(sizeof(char*), 100);
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

void create_token(t_data* data, char** pipe_split)
{
	t_token* last;
	t_token* new_node;
	char** token_split;
	int i;

	i = 0;
	last = NULL;
	while (pipe_split[i])
	{
		token_split = ft_split(pipe_split[i], ' ');
		if (!token_split)
			data_malloc_error(data);
		new_node = new_token(last, token_split, pipe_split[i]);
		if (!new_node)
			data_malloc_error(data);
		if (!data->token)
			data->token = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
}

void tokenization(t_data* data)
{
	char** pipe_split;

	if (data->token)
	{
		free_token(data->token);
		data->token = NULL;
	}
	pipe_split = ft_split(data->line, '|');
	if (!pipe_split)
		data_malloc_error(data);
	create_token(data, pipe_split);
	free_arr(pipe_split);
	free(data->line);
}
