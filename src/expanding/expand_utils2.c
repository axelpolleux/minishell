/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:51:32 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/01 11:59:07 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	void_quote(t_data *data, char *line, int *i, int *empty)
{
	if (data->quote == NQUOT)
	{
		if (line[*i] == '"' && line[*i + 1] == '"')
		{
			*(i) += 2;
			*empty = 1;
			return (1);
		}
	}
	if (data->quote == NQUOT)
	{
		if (line[*i] == '\'' && line[*i + 1] == '\'')
		{
			*(i) += 2;
			*empty = 1;
			return (1);
		}
	}
	return (0);
}

int	ext_nqote(char **old, int *i, int *j, int *l)
{
	while (old[*i][*j] == ' ')
		(*j)++;
	if (!old[*i][*j])
		return (1);
	*l = *j;
	*j += word_size(old[*i] + *j, ' ');
	return (0);
}

int	exec_line_expand(t_data *data, char *line, char **n_line, int **args)
{
	if (void_quote(data, line, args[0], args[1]))
		return (1);
	if (quote_expand(data, line, args[0]))
	{
		*args[1] = 1;
		return (1);
	}
	if (line[*args[0]] == '$' && data->quote != SQUOT)
	{
		*n_line = get_dollar(data, line, args[0], *n_line);
		if (!(*n_line))
			return (0);
		return (1);
	}
	if ((data->quote == DQUOT || data->quote == SQUOT) && line[*args[0]] == ' ')
		*n_line = ft_charjoin(*n_line, 1);
	else
		*n_line = ft_charjoin(*n_line, line[*args[0]]);
	if (!(*n_line))
		return (0);
	return (2);
}

bool	expand_redir(t_data *data, t_redir_her *doc)
{
	char		*new_line;

	if (!doc || !doc->file)
		return (false);
	data->quote = NQUOT;
	new_line = line_expand(data, doc->file, 0);
	if (!new_line)
		return (true);
	free (doc->file);
	doc->file = new_line;
	return (false);
}
