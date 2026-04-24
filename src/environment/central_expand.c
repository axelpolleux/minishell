/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:10:01 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/24 15:14:40 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	len = get_key_len(&line[*i], key);
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
	else if (line[*i] == '"' && data->quote == NQUOT)
	{
		data->quote = DQUOT;
		(*i)++;
		return (1);
	}
	else if (line[*i] == '"' && data->quote == DQUOT)
	{
		data->quote = NQUOT;
		(*i)++;
		return (1);
	}
	return (0);
}

char	*line_expand(t_data *data, char *line, int i)
{
	char	*n_line;
	char	*tmp;

	data->quote = NQUOT;
	n_line = ft_strdup("");
	while (line[i])
	{
		if (quote_expand(data, line, &i))
			continue ;
		if ((line[i] == '$' && data->quote != SQUOT))
		{
			i++;
			printf("pre_expand: {%s}\n", line);
			tmp = dollar_expand(data, line, &i);
			if (!tmp)
				return (NULL);
			n_line = ft_strjoin_upd(n_line, tmp);
			free(tmp);
			continue ;
		}
		n_line = ft_charjoin(n_line, line[i]);
		i++;
	}
	return (n_line);
}

// void	get_expand(t_data *data, t_cmd *cmd)
// {
// 	char	*new_line;
// 	int		i;

// 	i = -1;
// 	while (cmd->cmd[++i])
// 	{
// 		new_line = line_expand(data, cmd->cmd[i], 0);
// 		if (!new_line)
// 			data_malloc_error(data);
// 		free(cmd->cmd[i]);
// 		cmd->cmd[i] = new_line;
// 	}
// }
//======================teste=========================//
void	get_expand_t(t_data *data, char *line)
{
	char	*new_line;

	new_line = line_expand(data, line, 0);
	if (!new_line)
		data_malloc_error(data);
	printf("expand: {%s}\n", new_line);
	free(new_line);
}

// void	get_expand_t(t_data *data, t_token *token)
// {
// 	char	*new_line;

// 	while (token)
// 	{
// 		new_line = line_expand(data, token->cmd, 0);
// 		if (!new_line)
// 			data_malloc_error(data);
// 		free(token->cmd);
// 		token->cmd = new_line;
// 		printf("expand: {%s}\n", token->cmd);
// 		token = token->next;
// 	}
// }
//============================================================//
