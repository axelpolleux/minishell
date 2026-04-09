/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:01:08 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/09 17:57:35 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/lib/minishell.h"
#include "../../includes/libft/libft.h"



void	double_quotes(char *input, t_token **tokens, int *index)
{
	int		i;
	t_token	*token;

	if (input[*index] != 34)
		return ;
	i = 1;
	while (input[*index + i] && input[*index + i] != 34)
	{
		i++;
	}
	if (!input[*index + i])
		return ;
	token = token_new(ft_substr(input, *index + 1, i - 1), WORD);
	ft_token_add_back(tokens, token);
	(*index) += (i + 1);
}

