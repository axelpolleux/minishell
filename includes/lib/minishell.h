/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/05 18:39:55 by ethutin-         ###   ########.fr       */
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
extern volatile int	g_signal;

# define ERROR		0
# define WORD		1
# define PIPE		2 // |
# define RED_IN		3 // <
# define RED_OUT	4 // >
# define APPEND		5 // >>
# define HEREDOC	6 // <<
# define CMD		7

# define P_ERROR	0
# define C_ERROR	1
# define NF 		-1

# define NQUOT		0
# define SQUOT		1
# define DQUOT		2

# define PATH		"PATH"
# define PWD		"PWD"
# define OLDPWD		"OLDPWD"
# define HOME		"HOME"

# define HOME_NSET	"minishell: cd: HOME not set\n"
# define OLDP_NSET	"minishell: cd: OLDPWD not set\n"
# define CD_ER		"minishell: cd"
# define CD_ARG		"minishell: cd: too many arguments\n"
# define PWD_ER		"minishell: pwd"
# define EXT_ARG	"exit\nminishell: exit: too many arguments\n"
# define QUOT_ER	"minishell: every quote must be closed\n"
# define SYNT_ER	"minishell: syntax error near unexpected token `newline'\n"
# define DATA_ER	"Error : A malloc has failed\n"
//==============================================//

//====================<for all struct>===================//<<<<

typedef struct s_cmd
{
	char			**cmd;
	char			*cmd_path;
	char			*full_cmd;

	int				type;
	int				input;
	int				output;

	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_token
{
	char			*cmd;

	int				type;

	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*arg;
	char			*key;

	int				export;

	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	char		**path;
	char		**built_in;
	char		**built_env;

	char		*line;
	char		*line_env;

	int			fd_storage[2];
	int			last_fd;
	int			exit;
	int			quote;
	

	//pid_t		*pid;

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
void			error_perror(char *error, int error_p, int fd);
void			error_export(char *error);
void			error_exit(t_data *data, char *error);
void			error_quote(void);
//void			error_signal(int signal);
void			exec_fail(t_data *data);
void			init_env_fail(t_data *data, char *new_env, char *new_arg, char *new_key);
void			init_env_fail_n(char *new_env, char *new_arg, char *new_key);

int				data_malloc_error(t_data *data);
int				open_error(t_data *data);
//=======================================================//

//==================<general fonction>====================//
char			**tab_env(t_env *env, int i);
char			*arg_env(char **env, char *motif, int len);
char			*ft_charjoin(char *str, char c);
char			*ft_strjoin_upd(char *s1, char *s2);

void			*free_arr(char **str);
void			closes(int fd, int *fd_storage);
void			free_data(t_data *data);
void			free_env(t_env *node);
void			free_token(t_token *node);
void			free_cmd(t_cmd *node);
void			add_to_bottom_env(t_env **node, t_env *new_bot);
void			add_to_bottom_cmd(t_cmd **node, t_cmd *new_bot);
void			env_new_node(t_data *data, char *line);
//void			reset(t_data *data);
//================================================================//
void			display_env(t_env *view);// a degager a la fin
void			display_token(t_token *view);//
void			display_cmd(t_cmd *view);//
//================================================================//
int				ft_strcmp(char *s1, char *s2);
int				srch_cmd(char *s, char c);
int				ft_lstsize_e(t_env *lst);
int				ft_lstsize_t(t_token *lst);
int				ft_lstsize_c(t_cmd *lst);
int				nb_arg(char **ar);
int				no_minim_env(char **env);
int				key_in_env(t_data *data, char *key);
int				only_key(char *line); //if only_key succed 0 is return, on error an int representing the number caratere composing the key is return ('=' is not comprise)
int 			init_champ_env(t_data *data, char **new_var, char **new_arg, char **new_key);

t_data			*init_data(int ac, char **av);
t_env			*new_env(char *new_var, char *new_arg, char *new_key, int export);
t_env			*make_new_env(char *line, char *name, int export, int key);
t_env			*make_new_env_name(char *line, int export);
//======================================================//

//============for the the expand========//
char			**get_expand_t(t_data *data, char **cmd);
char			*dollar_expand(t_data *data, char *line, int *i);
char			*line_expand(t_data *data, char *line, int i);
char			*get_dollar(t_data *data, char *line, int *i, char *n_line);

void			replace_cmd(t_data *data, t_cmd *cmd, char **tmp);
void			place_space(char **args);
void			get_expand(t_data *data, t_cmd *cmd);

int				split_nquote(char **new, char **old, int i, int k);
int				get_key_nd_len(char *line, char *name);
int				quote_expand(t_data *data, char *line, int *i);
int				count_word_quot(char **arr, char c);
//=====================================//

//========================<for build in>=========================//
char			**tri_alpha(t_env *env);
char			**init_built(void);
char			*get_arg_env(t_data *data, char *motif);
char			*path_env(t_data *data, char **cmd);

void			print_flag(char **cmd, int start);
void			built_choice(t_data *data, t_cmd *cmd);
void			built_parent(t_data *data, t_cmd *cmd);
void			unset_place(t_data *data, char *motif);
void			exec_exit(t_data *data, t_cmd *g_cmd, char **cmd);
void			exec_built(t_data *data, t_cmd *cmd);
void			manage_export(t_data *data, char *line);
void			make_export(t_data *data, char *key);
void			change_arg(t_data *data, char *line, char *name, int start);
//void			make_export_equal(t_data *data, char *key);

int				make_built_env(t_data *data, t_env *new, char **env);
int				is_builtin(char **built_in, char *cmd);
int				exit_atoi(const char *str, int sign, long res);
int				exec_echo(char **cmd);
int				exec_cd(t_data *data, char **cmd);
int				exec_chdir(char *path, char *new_pwd, size_t size);
int				exec_pwd(void);
int				exec_export(t_data *data, char **cmd);
int				central_export(t_data *data, char **cmd);
int				exec_unset(t_data *data, char **cmd);
int				exec_env(t_data *data);
int				update_var(t_data *data, char *new_pwd, char *old_pwd);
int				replace(t_data *data, char *motif, char *path);
int				only_export(t_data *data, char **cmd);
int				word_size(char *str, char charset);
int				count_export(t_env *env);
int				only_key_equal(char *line);
int				realoc_arg(t_env *tmp, char *line, char *name, int start);
//===============================================================//

//========================<for exec>=========================//
char			**get_path(t_data *data, int len);

void			verif_command(t_data *data, t_cmd *cmd);
void			children(t_data *data, t_cmd *cmd);
void			cmd_whith_path(t_data *data, char *command);
void			full_cmd(t_data *data, char *command);
void			exec_command(t_data *data, char **env);
void			parent(t_data *data, t_cmd *cmd);
void			manage_process(t_data *data, t_cmd *cmd);
void			wait_end(t_data *data);
void			manage_redir(t_data *data, t_cmd *cmd);
void			in_hre(t_data *data, int fd[2]);
void			exec(t_data *data);

int				get_cmd_path(t_data *data, t_cmd *cmd);
int				here_doc_manage(t_data *data);
int				verif_file(char *line, int doc);
int				nb_process(t_cmd *cmd);
int				only_quote(char *line);
int				get_enof(t_data *data, char *line);
int				full_void(char *line);

//===========================================================//

//========================<for the parsing>=========================//
char			**tokens_to_argv(t_token *start, t_token *end);

void			main_reading(t_data *data, char *title);
void			display_tokens(t_token *token);
void			main_parser(t_data *data);
void			ft_token_add_back(t_token **lst, t_token *new);
void			double_quotes(t_data *data, t_token **tokens,	\
								char *input, int *index);
void			single_quotes(t_data *data, t_token **tokens,	\
								char *input, int *index);
void			add_cmd_back(t_cmd **lst, t_cmd *new);

int				main_parser(t_data *data);
int				is_space(int c);
int				not_in_original_en(char **env, char *name);
int				make_oldpwd(t_data *data, t_env *new, char **env);
int				make_pwd(t_data *data, t_env *new);
int				no_minim_env(char **env);
int				count_words(t_token *start, t_token *end);

t_cmd			*new_cmd_node(void);
t_cmd			*init_cmd(t_token *tokens);
t_token			*tokeniser(t_data *data, char *input);
t_token			*token_new(char *input, int *index, int len, int type);


//======================================================//

//===================<for sig usage>===============//
void			ft_signal_d(t_env *env);
void			ft_sigint_heredoc(int pid);
void			ft_sigint_cmd(int pid);
void			ft_sigint_interactive(int pid);

int				signal_manage(void);
//===============================================//

//==========================<Get Next Line>=====================//
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char			*get_next_line(int fd, size_t i);
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
