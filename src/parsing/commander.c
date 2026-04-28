/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:42:55 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/28 15:01:11 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*commander(t_token *tokens)
{
	t_cmd	*commands;
	int		i_cmd;
	int		i;

	commands = ft_calloc(1, sizeof(t_cmd *));
	if (!commands)
	{
		free_cmd(commands);
		return (0);
	}
	i_cmd = 0;
	i = 0;
	(void)tokens;
	// while (tokens)
	// {
	// 	while (tokens && tokens->type != PIPE)
	// 	{
	// 		tokens = tokens->next;
	// 	}
	// }
	return (commands);
}
