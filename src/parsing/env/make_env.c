/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:29:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 17:55:40 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pwd(t_data *data, t_env *new)
{
	char	*pwd;
	char	*new_var;
	char	*new_arg;
	char	*new_key;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);
	new_var = NULL;
	new_arg = NULL;
	new_key = NULL;
	data->line_env = ft_strjoin("PWD=", pwd);
	free (pwd);
	if (!data->line_env)
		return (EXIT_FAILURE);
	if (init_champ_env(data, &new_var, &new_arg, &new_key))
		init_env_fail_n(new_var, new_arg, new_key);
	new = new_env(new_var, new_arg, new_key, 1);
	if (!new)
		init_env_fail_n(new_var, new_arg, new_key);
	add_to_bottom_env (&data->t_env, new);
	free(data->line);
	data->line = NULL;
	return (EXIT_SUCCESS);
}

char	*get_oldpwd(t_data *data, char **env)
{
	char	*line;

	if (!env)
	{
		line = ft_strjoin("OLDPWD=", get_arg_env(data, PWD));
		if (!line)
			return (NULL);
	}
	else
	{
		line = ft_strdup(arg_env(env, "PWD=", ft_strlen("PWD=")));
		if (!line)
			return (NULL);
	}
	return (line);
}

int	make_oldpwd(t_data *data, t_env *new, char **env)
{
	char	*new_var;
	char	*new_arg;
	char	*new_key;

	new_var = NULL;
	new_arg = NULL;
	new_key = NULL;
	data->line = get_oldpwd(data, env);
	if (!data->line)
		return (EXIT_FAILURE);
	if (init_champ_env(data, &new_var, &new_arg, &new_key))
		init_env_fail_n(new_var, new_arg, new_key);
	new = new_env(new_var, new_arg, new_key, 1);
	if (!new)
		init_env_fail_n(new_var, new_arg, new_key);
	add_to_bottom_env (&data->t_env, new);
	free(data->line);
	data->line = NULL;
	return (EXIT_SUCCESS);
}

int	not_in_original_en(char **env, char *name)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)))
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	make_built_env(t_data *data, t_env *new, char **env)
{
	int		error;

	error = no_minim_env(env);
	if (error == -1)
		return (EXIT_FAILURE);
	if (error == 3)
	{
		if (make_pwd(data, new))
			data_malloc_error(data);
		if (make_oldpwd(data, new, NULL))
			data_malloc_error(data);
	}
	if (error == 2)
		if (make_pwd(data, new))
			data_malloc_error(data);
	if (error == 1)
		if (make_oldpwd(data, new, env))
			data_malloc_error(data);
	return (EXIT_SUCCESS);
}
