/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:11:46 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/31 21:22:20 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/libft/libft.h"

int	make_pwd(t_data *data, t_env *new)
{
	char	*args[4];

	ft_bzero(args, 4);
	args[0] = getcwd(NULL, 0);
	if (!args[0])
		return (EXIT_FAILURE);
	data->line_env = ft_strjoin("PWD=", args[0]);
	free(args[0]);
	if (!data->line_env)
		return (EXIT_FAILURE);
	if (init_champ_env(data, &args[1], &args[2], &args[3]))
		init_env_fail_n(args[1], args[2], args[3]);
	new = new_env(args[1], args[2], args[3], 1);
	free(data->line_env);
	data->line_env = NULL;
	if (!new)
		init_env_fail_n(args[1], args[2], args[3]);
	add_to_bottom_env (&data->t_env, new);
	free(data->line);
	data->line = NULL;
	return (EXIT_SUCCESS);
}
