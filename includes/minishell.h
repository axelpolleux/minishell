/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/19 10:38:09 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <signal.h>

//====================<for all struct>===================//

// typedef struct s_data
// {
// 	char		**path;
// 	char		**cmd_split;

// 	char		*path_and_cmd;
// 	char		*cmd_space_void;

// 	int			ac;
// 	int			fd_storage[2];
// 	int			cmd_null;
// 	int			cmd_invalid;
// 	int			path_invalid;
// 	int			path_void;
// 	int			path_null;

// 	pid_t		pid[2];

// }				t_data;

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,

} token_type;
//=======================================================//


#endif