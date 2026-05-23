/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:19:49 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/22 10:46:08 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	in_quote(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			return (true);
	}
	return (false);
}

char	*get_expand_line(t_data *data, char *line, char *n_line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			n_line = get_dollar(data, line, &i, n_line);
			if (!n_line)
				return (NULL);
		}
		else
		{
			n_line = ft_charjoin(n_line, line[i]);
			if (!n_line)
				return (NULL);
			i++;
		}
	}
	return (n_line);
}

char	*expand_here_doc(t_data *data, t_redir_her *doc, char *line, char *tmp)
{
	char	*n_line;
	char	*old;

	(void)doc;
	n_line = NULL;
	if (!in_quote(tmp))
	{
		n_line = ft_strdup("");
		if (!n_line)
			return (NULL);
		old = line;
		line = get_expand_line(data, line, n_line);
		free(old);
	}
	if (!line)
		free(tmp);
	return (line);
}
