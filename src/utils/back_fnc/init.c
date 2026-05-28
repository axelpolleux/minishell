/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:20:04 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/28 10:47:18 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *new_var, char *new_arg, char *new_key, int export)
{
	t_env	*new_node;

	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
		return (NULL);
	new_node->var = new_var;
	new_node->arg = new_arg;
	new_node->key = new_key;
	new_node->export = export;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

char	**init_built(void)
{
	char	**built_in;

	built_in = ft_calloc(sizeof(char *), 8);
	if (!built_in)
		return (NULL);
	built_in[0] = "echo";
	built_in[1] = "cd";
	built_in[2] = "pwd";
	built_in[3] = "export";
	built_in[4] = "unset";
	built_in[5] = "env";
	built_in[6] = "exit";
	built_in[7] = NULL;
	return (built_in);
}

t_env	*make_new_env_name(char *line, int export)
{
	t_env	*new_node;
	char	*new_var;
	char	*name;

	new_var = ft_strdup(line);
	if (!new_var)
		return (NULL);
	name = ft_strdup(line);
	if (!name)
	{
		free(new_var);
		return (NULL);
	}
	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
	{
		free(new_var);
		free(name);
		return (NULL);
	}
	new_node->var = new_var;
	new_node->arg = NULL;
	new_node->key = name;
	new_node->export = export;
	return (new_node);
}

void	init_env(t_data *data, char **env, int i)
{
	t_env	*new;
	char	*new_var;
	char	*new_arg;
	char	*new_key;

	new = NULL;
	new_var = NULL;
	new_arg = NULL;
	new_key = NULL;
	if (make_built_env(data, new, env))
		return ;
	while (env[++i])
	{
		data->line_env = env[i];
		if (init_champ_env(data, &new_var, &new_arg, &new_key))
			init_env_fail(data, new_var, new_arg, new_key);
		new = new_env(new_var, new_arg, new_key, 1);
		if (!new)
			init_env_fail(data, new_var, new_arg, new_key);
		add_to_bottom_env (&data->t_env, new);
	}
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		data_malloc_error(data);
	data->fd_storage[0] = -1;
	data->fd_storage[1] = -1;
	data->t_env = NULL;
	data->history = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->exit = 0;
	data->quote = NQUOT;
	(void)av;
	(void)ac;
	return (data);
}
