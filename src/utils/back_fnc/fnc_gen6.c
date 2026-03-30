/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/30 17:43:31 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char ** init_built(void)  //ou pourrait plus secu
{
	char    **built_in;

	built_in = ft_split("echo cd pwd export unset env exit", ' ');
	if (!built_in)
		return (NULL);
}