/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extend1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:40:43 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/26 18:38:51 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int command_proces(t_cmd *cmd)
{
    t_cmd   *tmp;
    int     count;

    count = 0;
    tmp = cmd;
    while (tmp)
    {
        if (tmp->type == CMD)
            count++;
        tmp = tmp->next;
    }
    return (count);
}
