/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/23 15:26:03 by ethutin-         ###   ########.fr       */
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

/* repecter l'ordre
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
# define CMD 1
# define PIPE 2 // |
# define OR 3 // ||
# define BACK 4 // &
# define RED_IN 5 // <
# define RED_OUT 6 // >
# define APPEND 7 // >>
# define HEREDOC 8 // <<
//==============================================//

//====================<for all struct>===================//
// typedef struct s_node
// {
// 	char			**cmd_part;
// 	char			*cmd;

// 	int				type;
// 	int				pos;

// 	struct s_node	*next;
// 	struct s_node	*prev;
// }	t_node;

typedef struct s_token
{
	char			**cmd_part;
	char			*cmd;

	int				type;
	int				pos;

	struct s_token	*next;
}	t_token;

typedef struct s_st_env
{
	char			*var;

	struct s_st_env	*next;
}	t_st_env;

typedef struct s_data
{
	char		**av;
	char		**path;
	char		**env;

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
	t_token		*token;
	t_st_env	*st_env;

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
void			free_env(t_st_env *node);
void			free_token(t_token *node);
void			add_to_bottom(t_st_env **node, t_st_env *new_bot);

int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				word_size(char *str, char charset);
int				srch_cmd(char *s, char c);
int				ft_lstsize(t_token *lst);

size_t			ft_strlen(const char *str);

t_data			*init_data(int ac, char **av);
t_token			*newnode(int i, int type, char **split_cmd);
t_st_env		*new_env(char *line);
//======================================================//

//========================<for exec>=========================//
char			**get_path(char **env, char *motif, t_data *data);

void			verif_command(t_data *d, char **env);
void			get_cmd_path(char *cmd, char **env, t_data *d);
void			children(t_data *data, char **av, char **env);
void			tennage(t_data *data, char **av);
void			process_manage(t_data *data, char **env, char **av);
void			cmd_whith_path(t_data *data, char *command);
void			full_cmd(t_data *data, char *command, int i);
void			exec_command(char **env, t_data *d);
void			parent(char **av, char **env, t_data *data);
void			here_doc_manage(t_data *data);

int				verif_file(char *line, int in, int doc);
//===========================================================//

//========================<for the parsing>=========================//
int				get_env(t_data *data, char **env);
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