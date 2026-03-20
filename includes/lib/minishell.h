/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/20 18:21:47 by ethutin-         ###   ########.fr       */
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

//=============<for general utility>=============//
# define CMD 1
# define PIPE 2
# define RED_IN 3
# define RED_OUT 4
# define APPEND 5
# define HEREDOC 6
# define VOID_CMD 7
//==============================================//

//====================<for all struct>===================//
typedef struct s_node
{
    char            **cmd_part;
    char            *cmd;

	int				type;
	int				pos;
	struct s_node	*next;
}	t_node;

typedef struct s_data
{

	char		**path;

	char		*path_and_cmd;
	char		*cmd_space_void;
	char		*limit;

	int			ac;
	int			cmd_n;
	int			fd_storage[2];
	int			fd;
	int			last_fd;
	int			doc;
	int			start;

	int			cmd_null;
	int			cmd_invalid;
	int			path_invalid;
	int			path_void;
	int			path_null;


	int			executable;

	pid_t		*pid;

    t_node     *node;

}				t_data;
//=======================================================//

//=================<for all type of error>================//
void			command_error(t_data *data);
void			null_command(t_data *data);
void			null_path(t_data *data);
void			void_path(t_data *data);
void			pipe_error(t_data *data);

int				ac_error(void);
int				malloc_error(char **path);
int				data_malloc_error(t_data *data);
int				open_error(t_data *data, char **av, int cmd);
//=======================================================//

//==================<general fonction>====================//
char			**ft_split(char const *s, char c);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(char *src);
char			*ft_strjoin(char const *s1, char const *s2);

void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*free_arr(char **str);
void			*ft_memset(void *s, int c, size_t n);
void			closes(int fd, int *fd_storage);
void			*ft_calloc(size_t nmemb, size_t size);
void			free_data(t_data *data);

int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				word_size(char *str, char charset);
int				srch_cmd(char *s, char c);

size_t			ft_strlen(const char *str);

t_data			*init_data(int ac);
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


#endif