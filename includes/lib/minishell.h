/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/01 18:24:39 by apolleux         ###   ########.fr       */
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

/* respecter l'ordre
	char
	void
	double
	unsign
	int
	long
	size_t
	strcut
*/

//=============<for general utility>=============//
# define WORD		1
# define PIPE		2 // |
# define RED_IN		3 // <
# define RED_OUT	4 // >
# define APPEND		5 // >>
# define HEREDOC	6 // <<
//==============================================//

//====================<for all struct>===================//
typedef struct s_token
{
	int				type;
	char			*cmd;

	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

// typedef struct s_data
// {
// 	char		**path;
//
// 	// char		*path_and_cmd;
// 	// char		*cmd_space_void;
// 	// char		*limit;
// 	char		*line;
//
// 	int			fd_storage[2];
// 	int			fd;
// 	int			last_fd;
// 	// int			doc;
// 	int			start;
//
// 	// int			cmd_null;
// 	// int			cmd_	struct s_cmd*next;
// 	// int			path_invalid;
// 	// int			path_void;
// 	// int			path_null;
// 	// int			executable;
// 	pid_t		*pid;
// 	t_token		*token;
// 	t_env		*env;
// 	//t_cmd		*cmd;
// }				t_data;

//========================<for the parsing>=========================//
char			*main_reading(char *title);
int				main_parser(char *input);
t_token			*tokeniser(char *input);

//======================================================//

//==========================<Get Next Line>=====================//
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char			*get_next_line_e(int fd, size_t i);
char			*line_add(char const *s1, char const *s2, size_t size);
char			*read_line(int fd, char **buffer_ptr, char *line, size_t i);
char			*verif_read_line(ssize_t r, char *line, char **buf_ptr);
char			*clean_buff(char *buffer);

void			*ft_memset(void *s, int c, size_t n);
void			free_line(char **line, char *new_line);
void			buffer_left(char *buffer, size_t start);

int				init_buff(char **buffer);
//===========================================================//
char			*get_word(char *s, int *i);
int				is_space(char c);
int				is_operator(char c);

#endif