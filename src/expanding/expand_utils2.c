/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:51:32 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/28 14:53:26 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	void_quote(t_data *data, char *line, int *i, int *empty)
{
	(void)data;
	if (line[*i] == '"' && line[*i + 1] == '"')
	{
		*(i) += 2;
		*empty = 1;
		return (1);
	}
	if (line[*i] == '\'' && line[*i + 1] == '\'')
	{
		*(i) += 2;
		*empty = 1;
		return (1);
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

int	exec_line_expand(t_data *data, char *line, char **n_line, int *i, int *empty)
{
	if (void_quote(data, line, i, empty))
		return (1);
	if (quote_expand(data, line, i))
		return (1);
	if (line[*i] == '$' && data->quote != SQUOT)
	{
		*n_line = get_dollar(data, line, i, *n_line);
		if (!(*n_line))
			return (0);
		return (1);
	}
	if (data->quote == DQUOT && line[*i] == ' ')
		*n_line = ft_charjoin(*n_line, 1);
	else
		*n_line = ft_charjoin(*n_line, line[*i]);
	if (!(*n_line))
		return (0);
	return (2);
}
