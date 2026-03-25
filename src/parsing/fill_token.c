/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:46:52 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/25 17:46:22 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// int main(int ac, char **av)
// {
//     (void)ac;
//     if (!main_token(av[1]))
//         printf("Didn't work !\n");
//     return (0);
// }

