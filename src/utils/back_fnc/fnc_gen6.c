/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/31 13:29:28 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char ** init_built(void)  //ou pourrait pluss secu
{
	char    **built_in;

	built_in = ft_split("echo cd pwd export unset env exit", ' ');
	if (!built_in)
		return (NULL);
	return (built_in);
}