/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/03/26 14:22:36 by ethutin-         ###   ########.fr       */
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
# define CMD		1
# define PIPE		2 // |
# define OR			3 // ||
# define BACK		4 // &
# define RED_IN		5 // <
# define RED_OUT	6 // >
# define APPEND		7 // >>
# define HEREDOC	8 // <<
# define OTHERS		9
//==============================================//

//====================<for all struct>===================//
typedef struct s_token
{
	int				type;
	char			*cmd;

	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*var;

	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	char		**path;

	// char		*path_and_cmd;
	// char		*cmd_space_void;
	// char		*limit;
	char		*line;

	int			fd_storage[2];
	int			fd;
	int			last_fd;
	// int			doc;
	int			start;

	// int			cmd_null;
	// int			cmd_	struct s_cmd*next;
	// int			path_invalid;
	// int			path_void;
	// int			path_null;
	// int			executable;
	pid_t		*pid;
	t_token		*token;
	t_env		*env;
	//t_cmd		*cmd;
}				t_data;
//=======================================================//

//=================<for all type of error>================//
void			command_error(t_data *data);
void			null_command(t_data *data);
void			null_path(t_data *data);
void			void_path(t_data *data);
void			pipe_error(t_data *data);

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
void			free_env(t_env *node);
void			free_token(t_token *node);
void			add_to_bottom(t_env **node, t_env *new_bot);

void			display_env(t_env *view);// a degager
void			display_token(t_token *view);//

int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_strcmp(char *s1, char *s2);
int				word_size(char *str, char charset);
int				srch_cmd(char *s, char c);
int				ft_lstsize_e(t_env *lst);
int				ft_lstsize_t(t_token *lst);
int				exit_shell(char *line);

size_t			ft_strlen(const char *str);

t_data			*init_data(int ac, char **av);
t_token			*new_token(t_token *node, char *cmd);
t_env			*new_env(char *line);
//======================================================//

//========================<for build in>=========================//
char			**tab_env(t_env *env);
char			**tri_alpha(t_env *env);

void			export_central(t_data *data);
//===============================================================//

//========================<for exec>=========================//
char			**get_path(char **env, char *motif, t_data *data);

void			verif_command(t_data *d, char **env);
void			get_cmd_path(char *cmd, char **env, t_data *d);
void			children(char *line, t_data *data);
void			tennage(t_data *data, char **av);
void			process_manage(char *line, t_data *data);
void			cmd_whith_path(t_data *data, char *command);
void			full_cmd(t_data *data, char *command, int i);
void			exec_command(char **env, t_data *d);
void			parent(char *line, t_data *data);
void			here_doc_manage(t_data *data);

int				verif_file(char *line, int in, int doc);
//===========================================================//

//========================<for the parsing>=========================//
char			**token_split(char *str);

char			*get_word(char *s, int *i);

void			get_new(int i, char *line, char **env, t_data *data);
void			tokenization(t_data *data);
void			create_token(t_data *data, char **pipe_split);

int				get_env(t_data *data, char **env);
int				space(char c);
int				quote(char c);
int				get_len(int i, int count, char *str);
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