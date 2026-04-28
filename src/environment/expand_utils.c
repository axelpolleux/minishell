/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:01:58 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/28 19:17:20 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dollar(t_data *data, char *line, int *i, char *n_line)
{
	char	*tmp;

	(*i)++;
	printf("pre_expand: {%s}\n", line);
	tmp = dollar_expand(data, line, i);
	if (!tmp)
		return (NULL);
	n_line = ft_strjoin_upd(n_line, tmp);
	free(tmp);
	return (n_line);
}

int	count_word_quot(char **arr, char c)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = -1;
	while (arr[++i])
	{
		printf ("line:{%s}\n", arr[i]);
		j = 0;
		while (arr[i][j])
		{
			if ((arr[i][j] != c))
			{
				j += word_size(arr[i] + j, c);
				count++;
			}
			else if (arr[i][j] == c)
			j++;	
		}
	}
	printf ("count:{%d}\n", count);
	return (count);
}

void	place_space(char **arr)
{
	int i;
	int	j;

	i = -1;
	j = 0;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] == 1)
				arr[i][j] = ' ';
		}
	}
}

int	get_key_nd_len(char *line, char *name)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	if (!ft_isalpha(line[i]) && line[i] != '_')
		return (0);
	while (ft_isalnum(line[i]) || line[i] == '_')
	{
		if (i >= PATH_MAX - 1)
			break ;
		name[i] = line[i];
		i++;
	}
	name[i] = '\0';
	return (i);
}

int	quote_expand(t_data *data, char *line, int *i)
{
	if (line[*i] == '\'' && data->quote == NQUOT)
	{
		data->quote = SQUOT;
		(*i)++;
		return (1);
	}
	else if (line[*i] == '\'' && data->quote == SQUOT)
	{
		data->quote = NQUOT;
		(*i)++;
		return (1);
	}
	else if (line[*i] == '\"' && data->quote == NQUOT)
	{
		data->quote = DQUOT;
		(*i)++;
		return (1);
	}
	else if (line[*i] == '\"' && data->quote == DQUOT)
	{
		data->quote = NQUOT;
		(*i)++;
		return (1);
	}
	return (0);
}
