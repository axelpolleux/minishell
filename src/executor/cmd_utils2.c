/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:38:06 by apolleux          #+#    #+#             */
/*   Updated: 2026/06/01 16:44:35 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(t_data *data)
{
	char	*path_env;

	path_env = get_arg_env(data, "PATH");
	if (data->path)
		free_arr(data->path);
	if (path_env)
		data->path = ft_split(path_env, ':');
	else
		data->path = NULL;
}
