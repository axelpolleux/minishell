/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:06:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/20 17:48:03 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_chdir(char *path, char *new_pwd, size_t size)
{
	if (chdir(path) == -1 || !getcwd(new_pwd, size))
	{
		error_perror (CD_ER, C_ERROR, NF);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	replace(t_data *data, char *motif, char *path)
{
	t_env	*tmp;
	char	*var;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, motif, ft_strlen(motif)))
		{
			var = ft_strjoin(motif, path);
			if (!var)
				data_malloc_error(data);
			free(tmp->var);
			tmp->var = var;
			tmp->arg = path;
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

	// if (!tmp) // dans replacepas sur au cas ou 
	// {
	// 	make_env(data, var);
	// 	replace(data, motif, path);
	// }

int	update_var(t_data *data, char *new_pwd, char *old_pwd)
{
	if (!new_pwd || !old_pwd)
		return (EXIT_FAILURE);
	if (replace(data, OLDPWD, old_pwd) == -1)
		return (EXIT_FAILURE);
	if (replace(data, PWD, new_pwd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*path_env(t_data *data, char **cmd)
{
	char	*path;

	path = NULL;
	if (!cmd[1])
	{
		path = get_var_env(data, HOME, ft_strlen(HOME));
		if (!path)
			error_perror (HOME_NSET, P_ERROR, 2);
	}
	else if (!strcmp(cmd[1], "-"))
	{
		path = get_var_env(data, OLDPWD, ft_strlen(OLDPWD));
		if (!path)
			error_perror (OLDP_NSET, P_ERROR, 2);
		else
			printf("%s\n", path);
	}
	else
		path = cmd[1];
	return (path);
}

int	exec_cd(t_data *data, char **cmd)
{
	char	new_pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*path;

	if (nb_arg(cmd) > 2)
	{
		error_perror (CD_ARG, P_ERROR, 2);
		return (EXIT_FAILURE);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		error_perror (CD_ER, C_ERROR, NF);
		return (EXIT_FAILURE);
	}
	path = path_env(data, cmd);
	if (!path)
		return (EXIT_FAILURE);
	if (exec_chdir(path, new_pwd, sizeof(new_pwd)))
		return (EXIT_FAILURE);
	if (update_var(data, new_pwd, old_pwd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
