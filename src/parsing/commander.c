/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:16:55 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/23 18:14:12 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:44:12 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/23 15:10:00 by Junie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "minishell.h"

int	count_words(t_token *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens && tokens->type != PIPE)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

t_cmd	*commander(t_token *tokens)
{
	t_cmd	*commands;

	commands = NULL;
	while (tokens)
	{
		printf("%d", count_words(tokens));
	}
	return (commands);
}
