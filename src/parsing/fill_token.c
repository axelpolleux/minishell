/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:46:52 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/25 17:20:47 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

// main token
// split command into tokens
// define token into type

int main_token(char *input)
{
    char    **splitted;
    int     i;

    i = 0;
    splitted = malloc(sizeof(char **));
    if (!splitted)
    {
        free(splitted);
        return (0);
    }
    splitted = ft_split(input, ' ');
    while (splitted[i])
    {
        printf("%s", splitted[i]);
        i++;
    }
    return (1);
}

int main(int ac, char **av)
{
    (void)ac;
    if (!main_token(av[1]))
        printf("Didn't work !\n");
    return (0);
}

