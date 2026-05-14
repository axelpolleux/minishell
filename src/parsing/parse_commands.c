/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 15:30:11 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_env(t_data *data, char *motif)
{
	t_env	*tmp;
	char	*path;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, motif))
		{
			path = tmp->arg;
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_builtin(char **built_in, char *cmd)
{
	int	i;

	i = 0;
	if (built_in == NULL)
		return (0);
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

t_cmd	*ft_cmd_new(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (0);
	return (new);
}

t_cmd	*parse_commands(t_token *tokens)
{
	t_cmd	*res;

	res = ft_cmd_new();
	while (tokens->type != WORD)
		tokens = tokens->next;
	res->command = ft_strdup(tokens->cmd);
	if (!res->command)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
