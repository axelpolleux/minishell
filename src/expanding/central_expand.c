/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:10:01 by ethutin-          #+#    #+#             */
/*   Updated: 2026/06/01 11:06:14 by ethutin-         ###   ########.fr       */
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
		if (old[i][0] == 2 && old[i][1] == '\0')
		{
			new[++k] = ft_strdup("");
			if (!new[k])
				return (EXIT_FAILURE);
			continue ;
		}
		while (old[i][j])
		{
			if (ext_nqote(old, &i, &j, &l))
				break ;
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
	{
		n_line = ft_strdup("$");
		return (n_line);
	}
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->exit));
	}
	len = get_key_nd_len(&line[*i], key);
	if (len == 0)
	{
		n_line = ft_strdup("$");
		return (n_line);
	}
	n_line = (get_arg_env(data, key));
	*i += len;
	if (!n_line)
		return (ft_strdup(""));
	return (ft_strdup(n_line));
}

char	*line_expand(t_data *data, char *line, int i)
{
	char	*n_line;
	int		ret;
	int		empty;

	empty = 0;
	n_line = ft_strdup("");
	if (!n_line)
		return (NULL);
	while (line[i])
	{
		ret = exec_line_expand(data, line, &n_line, (int *[2]){&i, &empty});
		if (ret == 0)
			return (NULL);
		if (ret == 2)
			i++;
	}
	if (empty && n_line[0] == '\0')
	{
		free(n_line);
		n_line = NULL;
		n_line = ft_strdup("\2");
	}
	return (n_line);
}

void	replace_cmd(t_data *data, t_cmd *cmd, char **tmp)
{
	char	**n_cmd;

	n_cmd = ft_calloc(sizeof(char *), count_word_quot(tmp, ' ', -1) + 1);
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
	free_arr(cmd->args);
	cmd->args = n_cmd;
}

void	get_expand(t_data *data, t_cmd *cmd)
{
	char	**tmp;
	char	*n_line;
	int		i;

	if (!cmd->args)
		return ;
	tmp = ft_calloc(sizeof(char *), nb_arg(cmd->args) + 1);
	if (!tmp)
		data_malloc_error(data);
	i = -1;
	while (cmd->args[++i])
	{
		data->quote = NQUOT;
		n_line = line_expand(data, cmd->args[i], 0);
		if (!n_line)
			data_malloc_error(data);
		tmp[i] = n_line;
	}
	replace_cmd(data, cmd, tmp);
	if (cmd->command)
		free(cmd->command);
	if (cmd->args && cmd->args[0])
		cmd->command = ft_strdup(cmd->args[0]);
}
