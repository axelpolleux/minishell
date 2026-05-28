/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:31:49 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/28 18:18:48 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool flag_identification(char *str)
{
    int i;

	i = 0;
    if (!str)
        return (false);
    if (str[i] != '-')
        return (false);
    i++;
    if (str[i] != 'n')
        return (false);
    while (str[i] == 'n')
        i++;
    return (str[i] == '\0');
}

void	print_flag(char **cmd, int start)
{
	int	firts_word;

	firts_word = 1;
	while (cmd[start])
	{
		if (ft_strlen(cmd[start]) != 0)
		{
			if (firts_word)
			{
				printf("%s", cmd[start]);
				firts_word = 0;
			}
			else
				printf(" %s", cmd[start]);
		}
		start++;
	}
}

int exec_echo(char **cmd)
{
    int i;
    bool new;

    i = 1;
    new = true;
    while (flag_identification(cmd[i]))
    {
        new = false;
        i++;
    }
    while (cmd[i])
    {
        printf("%s", cmd[i]);

        if (cmd[i + 1])
            printf(" ");
        i++;
    }
    if (new)
        printf("\n");
    return (0);
}
