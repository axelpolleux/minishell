/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:01:10 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/07 09:39:04 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(t_token *start, t_token *end)
{
	int	count;

	count = 0;
while (start && start != end)
	{
		if (start->type != PIPE)
			count++;
		start = start->next;
	}
	return (count);
}
