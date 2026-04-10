/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:14:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/09 11:15:30 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (line[i] != '\'' && line[i] != '\"')
			return (0);
	return (1);
}

t_token	*new_token(t_token *prev, char *cmd)
{
	t_token	*new_node;

	new_node = ft_calloc(sizeof(t_token), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->type = 0;
	new_node->cmd = cmd;
	new_node->next = NULL;
	new_node->prev = prev;
	return (new_node);
}

t_env	*new_env(char *line)
{
	t_env	*new_node;

	int i;

	i = 0;
	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->var = line;
	while (line[i] != '=')
		i++;
	new_node->arg = line + i + 1;
	new_node->export = 1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->path)
			free_arr(data->path);
		if (data->built_in)
			free_arr(data->built_in);
		if (data->built_env)
			free_arr(data->built_env);
		if (data->pid)
			free(data->pid);
		if (data->line)
			free(data->line);
		if (data->token)
			free_token(data->token);
		if (data->t_env)
			free_env(data->t_env);
		if (data->cmd)
			free_cmd(data->cmd);
		free(data);
	}
}

int	full_void(char *line)
{
	int	i;

	i = -1;
	if (line)
	{
		while (line[++i])
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
				return (0);
	}
	return (1);
}
