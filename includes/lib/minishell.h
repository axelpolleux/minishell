/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/08 13:56:08 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
# include <limits.h>

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
# define OTHERS		9 // ????????

# define PATH		"PATH="
# define PWD		"PWD="
# define OLDPWD		"OLDPWD="
# define HOME		"HOME="

# define HOM_NSET	"minishell: cd: HOME not set\n"
# define OLDP_NSET	"minishell: cd: OLDPWD not set\n"
# define CD_ER		"minishell: cd"
# define CD_ARG		"minishell: cd: too many arguments\n"

# define P_ERROR 0
# define C_ERROR 1
# define NF 0
//==============================================//

//====================<for all struct>===================//

typedef struct s_cmd
{
	char 			**cmd;
	char 			*cmd_path;
	char 			*full_cmd;

	int				type;
	int 			input;
	int				output;

	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_token
{
	char			*cmd;
	
	int				type;

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
	char		**built_in;
	char		**built_env;

	char		*line;
	// char		*error_line;

	int			fd_storage[2];
	int 		last_fd;
	int			exit;

	pid_t		*pid;
	
	t_token		*token;
	t_env		*t_env;
	t_cmd		*cmd;
}				t_data;
//=======================================================//

//=================<for all type of error>================//
void			pipe_error(t_data *data);
void			wait_error(t_data *data);
void			dup_error(t_data *data);
void			fork_error(t_data *data);
void			error_exit(char *error, int error_p, int fd);

int				malloc_error(char **path);
int				data_malloc_error(t_data *data);
int				open_error(t_data *data);
//=======================================================//

//==================<general fonction>====================//
char			**tab_env(t_env *env);
char			**ft_split(char const *s, char c);

char			*ft_substr(char const *s, unsigned int start, size_t len);
//char			*ft_strdup(char *src);
char			*ft_strjoin(char const *s1, char const *s2);

void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*free_arr(char **str);
void			*ft_memset(void *s, int c, size_t n);
void			closes(int fd, int *fd_storage);
void			*ft_calloc(size_t nmemb, size_t size);
void			free_data(t_data *data);
void			free_env(t_env *node);
void			free_token(t_token *node);
void			free_cmd(t_cmd *node);
void			add_to_bottom(t_env **node, t_env *new_bot);

void			display_env(t_env *view);// a degager
void			display_token(t_token *view);//
void			display_cmd(t_cmd *view);//

//int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_strcmp(char *s1, char *s2);
int				word_size(char *str, char charset);
int				srch_cmd(char *s, char c);
int				ft_lstsize_e(t_env *lst);
int				ft_lstsize_t(t_token *lst);
int				ft_lstsize_c(t_cmd *lst);
int				exit_shell(char *line);
int				nb_arg(char **ar);

size_t			ft_strlen(const char *str);

t_data			*init_data(int ac, char **av);
t_token			*new_token(t_token *node, char *cmd);
t_env			*new_env(char *line);
//======================================================//

//============for the the expand========//
char			*expand(t_data *data, t_cmd *cmd);
//=====================================//


//========================<for build in>=========================//
char			**tri_alpha(t_env *env);
char			**init_built(void);

void			print_flag(char **cmd, int start);
void			export_central(t_data *data);
void			built_choice(t_data *data, t_cmd *cmd);

int				is_builtin(char **built_in, char *cmd);
int				exec_echo(char **cmd);
int				exec_cd(t_data *data, char **cmd);
int				exec_built(t_data *data, t_cmd *cmd);
int				exec_chdir(char *path, char *new_pwd, size_t size);
//===============================================================//

//========================<for exec>=========================//
char			**get_path(t_data *data, int len);

void			verif_command(t_data *data, t_cmd *cmd);
void			get_cmd_path(t_data *data, t_cmd *cmd);
void			children(t_data *data, t_cmd *cmd);
void			tennage(t_data *data);
void			exec(t_data *data);
void			cmd_whith_path(t_data *data, char *command);
void			full_cmd(t_data *data, char *command);
void			exec_command(t_data *data, char **env);
void			parent(t_data *data, t_cmd *cmd);
void			wait_end(t_data *data, int count);
void			manage_redir(t_data *data, t_cmd *cmd);

int				here_doc_manage(t_data *data);
int				verif_file(char *line, int doc);
int				nb_process(t_cmd *cmd);
int				only_quote(char *line);
int				get_enof(t_data *data, char *line);
int				full_void(char *line);

void			in_hre(t_data *data, int fd[2]);
//===========================================================//

//========================<for the parsing>=========================//
char			**token_split(char *str);
char			*get_word(char *s, int *i);

void			get_new(int i, char *line, char **env, t_data *data);
void			tokenization(t_data *data);
void			create_token(t_data *data, char **pipe_split);
void			get_env(t_data *data, char **env);

int				space(char c);
int				quote(char c);
int				get_len(int i, int count, char *str);
int				make_env(t_data *data, char **env);
//======================================================//

//==========================<Get Next Line_e>=====================//
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
//=============================================================//

#endif

