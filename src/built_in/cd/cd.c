/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:06:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/25 14:14:33 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_chdir(char *path, char *new_pwd, size_t size)
{
	if (chdir(path) == -1)
	{
		error_perror (CD_ER, C_ERROR, NF);
		return (EXIT_FAILURE);
	}
	if (!getcwd(new_pwd, size))
	{
		error_perror(CD_ER, C_ERROR, NF);
		new_pwd[0] = '\0';
	}
	return (EXIT_SUCCESS);
}

static int	get_old_pwd(t_data *data, char *old_pwd, size_t size)
{
	char	*pwd;

	if (getcwd(old_pwd, size))
		return (EXIT_SUCCESS);
	pwd = get_arg_env(data, PWD);
	if (pwd && ft_strlen(pwd) < size)
		ft_strlcpy(old_pwd, pwd, size);
	else
		old_pwd[0] = '\0';
	return (EXIT_SUCCESS);
}

int	replace(t_data *data, char *name, char *var)
{
	char	*new_var;
	char	*new_key;
	char	*new_arg;
	t_env	*new;

	data->line_env = ft_strjoin(name, var);
	if (!data->line_env)
		data_malloc_error(data);
	if (init_champ_env(data, &new_var, &new_arg, &new_key))
		data_malloc_error(data);
	if (update_cd(data, new_var, new_key, new_arg))
	{
		new = new_env(new_var, new_arg, new_key, 1);
		if (!new)
		{
			free(data->line_env);
			init_env_fail_n(new_var, new_arg, new_key);
			return (EXIT_FAILURE);
		}
		add_to_bottom_env(&data->t_env, new);
	}
	free(data->line_env);
	return (EXIT_SUCCESS);
}

int	update_var(t_data *data, char *new_pwd, char *old_pwd)
{
	if (!new_pwd || !old_pwd)
		return (EXIT_FAILURE);
	if (replace(data, "OLDPWD=", old_pwd))
		return (EXIT_FAILURE);
	if (replace(data, "PWD=", new_pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	exec_cd(t_data *data, char **args)
{
	char	new_pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*path;

	if (nb_arg(args) > 2)
	{
		error_perror(CD_ARG, P_ERROR, 2);
		return (EXIT_FAILURE);
	}
	if (get_old_pwd(data, old_pwd, sizeof(old_pwd)))
		return (EXIT_FAILURE);
	path = path_env(data, args);
	if (!path)
		return (EXIT_FAILURE);
	if (exec_chdir(path, new_pwd, sizeof(new_pwd)))
		return (EXIT_FAILURE);
	if (update_var(data, new_pwd, old_pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
