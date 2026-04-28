/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:10:01 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/28 19:15:17 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_nquote(char **new, char **old, int i, int k)
{
	int	j;
	int	l;

	while (old[++i])
	{
		j = 0;
		while (old[i][j])
		{
			while (old[i][j] == ' ')
				j++;
			if (!old[i][j])
			{
				new[++k] = ft_strdup("");
				if (!new[k])
					return (EXIT_FAILURE);
				continue ;
			}
			l = j;
			j += word_size(old[i] + j, ' ');
			new[++k] = ft_substr(old[i], l, j - l);
			if (!new[k])
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

char	*dollar_expand(t_data *data, char *line, int *i)
{
	char	*n_line;
	char	key[PATH_MAX];
	int		len;

	if (!line[*i])
		return (ft_strdup("$"));
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->exit));
	}
	len = get_key_nd_len(&line[*i], key);
	if (len == 0)
	{
		n_line = ft_strdup("$");
		if (!n_line)
			return (NULL);
		return (n_line);
	}
	n_line = (get_var_env(data, key));
	*i += len;
	if (!n_line)
		return (ft_strdup(""));
	return (ft_strdup(n_line));
}

char	*line_expand(t_data *data, char *line, int i)
{
	char	*n_line;

	n_line = ft_strdup("");
	if (!n_line)
		return (NULL);
	while (line[i])
	{
		if (quote_expand(data, line, &i))
			continue ;
		if (line[i] == '$' && data->quote != SQUOT)
		{
			n_line = get_dollar(data, line, &i, n_line);
			if (!n_line)
				return (NULL);
			continue ;
		}
		if (data->quote == DQUOT && line[i] == ' ')
			n_line = ft_charjoin(n_line, 1);
		else
			n_line = ft_charjoin(n_line, line[i]);
		if (!n_line)
			return (NULL);
		i++;
	}
	return (n_line);
}

void	replace_cmd(t_data *data, t_cmd *cmd, char **tmp)
{
	char	**n_cmd;

	n_cmd = ft_calloc(sizeof(char *), count_word_quot(tmp, ' ') + 1);
	if (!n_cmd)
	{
		free_arr(tmp);
		data_malloc_error (data);
	}
	if (split_nquote(n_cmd, tmp, -1, -1))
	{
		free_arr(tmp);
		free_arr(n_cmd);
		(data_malloc_error (data));
	}
	free_arr(tmp);
	place_space(n_cmd);
	free_arr(cmd->cmd);
	cmd->cmd = n_cmd;
}

void	get_expand(t_data *data, t_cmd *cmd)
{
	char	**tmp;
	char	*n_line;
	int		i;

	tmp = ft_calloc(sizeof(char *), PATH_MAX);
	if (!tmp)
		data_malloc_error(data);
	i = -1;
	while (cmd->cmd[++i])
	{
		data->quote = NQUOT;
		n_line = line_expand(data, cmd->cmd[i], 0);
		if (!n_line)
			data_malloc_error(data);
		printf("expand:%d:{%s}\n", i + 1, n_line);
		tmp[i] = n_line;
	}
	replace_cmd(data, cmd, tmp);
}

char	**get_expand_t(t_data *data, char **cmd)
{
	char	*n_line;
	char	**n_cmd;
	char	**tmp;
	int		i;

	if (!*cmd)
		return (NULL);
	tmp = ft_calloc(sizeof(char *), PATH_MAX);
	if (!tmp)
		return (NULL); //data_malloc_error(data);
	i = -1;
	while (cmd[++i])
	{
		data->quote = NQUOT;
		n_line = line_expand(data, cmd[i], 0);
		if (!n_line)
			data_malloc_error(data);
		printf("expand:%d:{%s}\n", i + 1, n_line);
		tmp[i] = n_line;
	}
	n_cmd = ft_calloc(sizeof(char *), count_word_quot(tmp, ' ') + 1);
	if (!n_cmd)
	{
		free_arr(tmp);
		return (NULL); //data_malloc_error (data);
	}
	if (split_nquote(n_cmd, tmp, -1, -1))
	{
		free_arr(tmp);
		free_arr(n_cmd);
		return(NULL); //data_malloc_error (data);
	}
	free_arr(tmp);
	place_space(n_cmd);
	return (n_cmd);
}



