/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:29:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/21 15:23:35 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_minim_env(char **env)
{
	int		i;
	int		error;

	if (!env || !(*env))
		return (-1);
	error = 0;
	i = -1;
	if (not_in_original_en(env, PWD))
		error += 2;
	if (not_in_original_en(env, OLDPWD))
		error += 1;
	return (error);
}

int	make_pwd(t_data *data, t_env *new)
{
	char	*pwd;
	char	*line;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);
	line = ft_strjoin(PWD, pwd);
	free (pwd);
	if (!line)
		return (EXIT_FAILURE);
	new = new_env(line, 1);
	if (!new)
	{
		free(line);
		return (EXIT_FAILURE);
	}
	add_to_bottom_env(&data->t_env, new);
	return (EXIT_SUCCESS);
}

int	make_oldpwd(t_data *data, t_env *new, char **env)
{
	char	*line;

	if (!env)
	{
		line = ft_strjoin(OLDPWD, get_var_env(data, PWD, ft_strlen(PWD)));
		if (!line)
			return (EXIT_FAILURE);
	}
	else
		line = var_env(env, PWD, ft_strlen(PWD));
	new = new_env(line, 1);
	if (!new)
	{
		free(line);
		return (EXIT_FAILURE);
	}
	add_to_bottom_env(&data->t_env, new);
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
	// printf("ERR=%d\n", error);
	if (error == 3)
	{
		// printf("les deux n'existe pas\n");
		if (make_pwd(data, new))
			data_malloc_error(data);
		if (make_oldpwd(data, new, NULL))
			data_malloc_error(data);
	}
	if (error == 2)
	{
		// printf("PWD existe pas\n");
		if (make_pwd(data, new))
			data_malloc_error(data);
	}
	if (error == 1)
	{
		// printf("OLDPWD existe pas\n");
		if (make_oldpwd(data, new, env))
			data_malloc_error(data);
	}
	return (EXIT_SUCCESS);
}
