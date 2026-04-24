/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:10:01 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/24 10:47:58 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_word(char *line, int size)
// {
// 	char	*dollar;
// 	int		i;

// 	i = 0;
// 	while (line[++i] && i < size)
// 		dollar[i - 1] = line[i];
// 	dollar[i - 1] = '\0';
// 	return (dollar);
// }

// void	pars_word(char *cmd, int *j)
// {
// 	int		i;

// 	i = 0;
// 	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
// 		return (EXIT_FAILURE);
// 	while (cmd[++i])
// 	{
// 		if (cmd[i] == '=')
// 			return (EXIT_SUCCESS);
// 		else if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
// 			return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// char *expand_word(t_data *data, char *line)
// {
// 	char	*new_line;
// 	char	*word;
// 	int		i;
// 	int		j;

// 	new_line = NULL;
// 	i = -1;
// 	while (line[++i])
// 	{
// 		j = 0;
// 		if (line[i] == '$')
// 		{
// 			pars_word(line + i + 1, j);
// 			if (!j)
// 			{	
// 			}
// 			word = get_word(line + i + 1, j);
// 			if (not_in_en)
// 				return(NULL);
// 		}
// 	}
// 	return (new_line);
// }

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
		// n_line = ft_strdup("$");
		// if (!n_line)
		// 	return (NULL);
		// return (n_line);
		return (ft_strdup("$"));
	}
	n_line = (get_var_env(data, key));
	*i += len;
	if (!n_line)
		return (ft_strdup(""));
	return (ft_strdup(n_line));
}

// a refaire pour les quote, version primitive 
char	*line_expand(t_data *data, char *line, int i)
{
	char	*n_line;
	char	*tmp;

	data->quote = NQUOT;
	n_line = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '\'' && data->quote == NQUOT)
			data->quote = SQUOT;
		else if (line[i] == '\'' && data->quote == SQUOT)
			data->quote = NQUOT;
		else if (line[i] == '"' && data->quote == NQUOT)
			data->quote = DQUOT;
		else if (line[i] == '"' && data->quote == DQUOT)
			data->quote = NQUOT;
		else if (line[i] == '$' && data->quote != SQUOT)
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
		else
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

void	get_expand_t(t_data *data, t_token *token)
{
	char	*new_line;

	while (token)
	{
		new_line = line_expand(data, token->cmd, 0);
		if (!new_line)
			data_malloc_error(data);
		free(token->cmd);
		token->cmd = new_line;
		printf("expand: {%s}\n", token->cmd);
		token = token->next;
	}
}
/*
gerer uniquement les quote le reste et pas demander
*/
