/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:36:22 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/31 20:48:07 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// our include
# include "libft.h"

// basics
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>

// system includes
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

# include <curses.h>
# include <term.h>
# include <dirent.h>

/* respecter l'ordre
	char
	void
	double
	unsign
	int
	bool
	long
	size_t
	strcut
*/

//=============<for general utility>=============//
extern volatile int	g_signal;

# define WORD		1
# define PIPE		2 // |
# define RED_IN		3 // <
# define RED_OUT	4 // >
# define APPEND		5 // >>
# define HEREDOC	6 // <<

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
# define TITLE		"minichevre$ "

# define HOME_NSET	"minichevre: cd: HOME not set\n"
# define OLDP_NSET	"minichevre: cd: OLDPWD not set\n"
# define CD_ER		"minichevre: cd"
# define CD_ARG		"minichevre: cd: too many arguments\n"
# define PWD_ER		"minichevre: pwd"
# define EXT_ARG	"exit\nminichevre: exit: too many arguments\n"
# define QUOT_ER	"minichevre: every quotes must be closed\n"
# define SYNT_UT	"minichevre: syntax error near unexpected token\n"
# define DATA_ER	"Error : A malloc has failed\n"
//==============================================//

//====================<for all struct>===================//<<<<

typedef struct s_redir_her
{
	char				*file;

	int					type;
	int					fd;

	struct s_redir_her	*next;
}	t_redir_her;

typedef struct s_expand_ctx
{
	char	**n_line;
	int		*i;
	int		*empty;
}	t_expand_ctx;

typedef struct s_cmd
{
	// command management
	char			*command;
	char			**args;
	char			*cmd_path;
	char			*full_cmd;

	// redir management
	int				input;
	int				output;

	// heredoc
	t_redir_her		*redir;

	// link nodes
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_token
{
	char			*cmd;

	int				type;

	bool			quot;
	struct s_token	*next;
	struct s_token	*prev;
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
	char		*history;

	int			fd_storage[2];
	int			last_fd;
	int			exit;
	int			quote;

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
void			error_perror(char *error, int error_p, int fd);
void			error_export(char *error);
void			error_exit(t_data *data, char *error);
void			init_env_fail(t_data *data, char *new_env, \
char *new_arg, char *new_key);
void			init_env_fail_n(char *new_env, char *new_arg, char *new_key);
void			opendir_error(t_data *data, char *error);
void			error_cnf(t_data *data, char *error);
void			parser_error(t_data *data, int output);

int				error_pars(int error);
int				data_malloc_error(t_data *data);
int				open_error(t_data *data);
//=======================================================//

//==================<general fonction>====================//
char			**tab_env(t_env *env, int i);
char			*arg_env(char **env, char *motif, int len);
char			*ft_charjoin(char *str, char c);
char			*ft_strjoin_upd(char *s1, char *s2);

void			closes(int fd, int *fd_storage);
void			*free_arr(char **str);
void			free_data(t_data *data);
void			free_env(t_env *node);
void			free_token(t_token *node);
void			free_cmd(t_cmd *node);
void			free_redir(t_redir_her *node);
void			add_to_bottom_env(t_env **node, t_env *new_bot);
void			add_to_bottom_cmd(t_cmd **node, t_cmd *new_bot);
void			add_redir_back(t_redir_her **lst, t_redir_her *new);
void			env_new_node(t_data *data, char *line);
void			init_env(t_data *data, char **env, int i);

int				ft_strcmp(char *s1, char *s2);
int				srch_cmd(char *s, char c);
int				ft_lstsize_e(t_env *lst);
int				ft_lstsize_t(t_token *lst);
int				ft_lstsize_c(t_cmd *lst);
int				nb_arg(char **ar);
int				no_minim_env(char **env);
int				key_in_env(t_data *data, char *key);
int				only_key(char *line);
int				init_champ_env(t_data *data, char **new_var, \
char **new_arg, char **new_key);

t_data			*init_data(int ac, char **av);
t_env			*new_env(char *new_var, char *new_arg, \
char *new_key, int export);
t_env			*make_new_env_name(char *line, int export);
//======================================================//

//============for the the expand========//
char			**get_expand_t(t_data *data, char **cmd);
char			*dollar_expand(t_data *data, char *line, int *i);
char			*line_expand(t_data *data, char *line, int i);
char			*get_dollar(t_data *data, char *line, int *i, char *n_line);
char			*expand_here_doc(t_data *data, t_redir_her *doc, \
char *line, char *tmp);
char			*get_expand_line(t_data *data, char *line, char *n_line);

void			replace_cmd(t_data *data, t_cmd *cmd, char **tmp);
void			place_space(char **args);
void			get_expand(t_data *data, t_cmd *cmd);

int				split_nquote(char **new, char **old, int i, int k);
int				get_key_nd_len(char *line, char *name);
int				quote_expand(t_data *data, char *line, int *i);
int				count_word_quot(char **arr, char c, int i);
int				void_quote(t_data *data, char *line, int *i, int *empty);
int				ext_nqote(char **old, int *i, int *j, int *l);
// int				exec_line_expand(t_data *data, char *line, \
// char **nline, int *i, int *empty);
int				exec_line_expand(t_data *data, char *line, char **n_line, int **args);


bool			in_quote(char *line);
//=====================================//

//========================<for build in>=========================//
char			**tri_alpha(t_env *env);
char			**init_built(void);
char			*get_arg_env(t_data *data, char *motif);
char			*path_env(t_data *data, char **cmd);

void			print_flag(char **cmd, int start);
void			print_words(char **args, int *i, int *first_word);
void			built_child(t_data *data, t_cmd *cmd);
void			built_parent(t_data *data, t_cmd *cmd);
void			unset_place(t_data *data, char *motif);
void			exec_exit(t_data *data, t_cmd *g_cmd, char **cmd);
void			exit_arg(t_data *data, char *str, int *out);
void			exec_built(t_data *data, t_cmd *cmd);
void			manage_export(t_data *data, char *line);
void			make_export(t_data *data, char *key);
void			change_arg(t_data *data, char *line, char *name, int start);

int				make_built_env(t_data *data, t_env *new, char **env);
int				is_builtin(char **built_in, char *cmd);
long			exit_atoi(const char *str, int sign, long res);
int				exec_echo(char **cmd);
int				exec_cd(t_data *data, char **cmd);
int				exec_chdir(char *path, char *new_pwd, size_t size);
int				exec_pwd(t_data *data);
int				exec_export(t_data *data, char **cmd);
int				central_export(t_data *data, char **cmd);
int				exec_unset(t_data *data, char **cmd);
int				exec_env(t_data *data);
int				update_var(t_data *data, char *new_pwd, char *old_pwd);
int				replace(t_data *data, char *name, char *var);
int				only_export(t_data *data, char **cmd);
int				word_size(char *str, char charset);
int				count_export(t_env *env);
int				only_key_equal(char *line);
int				realoc_arg(t_env *tmp, char *line, char *name, int start);
int				update_cd(t_data *data, char *new_var, \
char *new_key, char *new_arg);

bool			flag_identification(char *str);
//===============================================================//

//========================<for exec>=========================//
void			get_path(t_data *data);
void			children(t_data *data, t_cmd *cmd);
void			cmd_with_path(t_data *data, t_cmd *cmd, char *command);
void			full_cmd(t_data *data, t_cmd *cmd, char *command, int i);
void			exec_command(t_data *data, t_cmd *cmd, char **env);
void			parent(t_data *data, t_cmd *cmd);
void			handle_exec_loop(t_data *data, int count);
void			manage_process(t_data *data, t_cmd *cmd, int index);
void			wait_end(t_data *data, int count);
void			apply_redir(t_data *data, t_cmd *cmd);
void			redir_heredoc(t_redir_her *redir);
void			exec(t_data *data);

int				manage_redir(t_data *data, t_cmd *cmd);
int				check_directory(t_data *data, char *path);
int				check_cmd(t_data *data, t_cmd *cmd, int *status);
int				verif_file(char *line, int doc);
int				handle_out(t_cmd *cmd, t_redir_her *curr);
int				handle_in(t_cmd *cmd, t_redir_her *curr);
int				only_quote(char *line);
int				full_void(char *line);
int				init_heredoc(t_data *data, t_redir_her *doc);

bool			fcext(t_data *data, t_cmd *cmd, char *path, char *command);
bool			heredoc_manage(t_data *data, t_cmd *cmd);
//===========================================================//

//========================<lexer and parsing>=========================//
void			add_in(char *input, int *i, int *len, int *type);
void			add_out(char *input, int *i, int *len, int *type);
void			new_state(t_data *data, char *input, int *index);
//========================<lexer and parsing>=========================//
char			**tokens_to_argv(t_token *start, t_token *end, int i);

void			add_in(char *input, int *i, int *len, int *type);
void			add_out(char *input, int *i, int *len, int *type);
void			new_state(t_data *data, char *input, int *index);
void			reset_read(t_data *data);
void			main_reading(t_data *data);
void			ft_token_add_back(t_token **lst, t_token *new);
void			add_cmd_back(t_cmd **lst, t_cmd *new);
void			g_signal_init(void);
void			g_signal_while(t_data *data);
void			check_exit(t_data *data);

int				new_redirection(t_data *data, t_cmd *cmd, int type, char *file);
int				tok_to_cmd(t_data *data, t_cmd *cmd, char *str, int i);
int				parse_redir(t_data *data, t_token **token, t_cmd *cmd);
int				main_parser(t_data *data);
int				not_in_original_en(char **env, char *name);
int				make_oldpwd(t_data *data, t_env *new, char **env);
int				make_pwd(t_data *data, t_env *new);
int				no_minim_env(char **env);
int				count_words(t_token *start, t_token *end);

bool			new_cmd(t_data *data, t_cmd **cmd, t_token *token);
bool			is_redir(int type);
bool			is_space(int c);
bool			skip_quote(char *input, int *i);
bool			add_all(t_data *data, t_token **tokens, char *input, int *i);
bool			add_word(t_data *data, t_token **tokens, \
char *input, int *index);
bool			quote_state(t_data *data, char *input, int *i, bool *quoted);
bool			write_here(t_redir_her *doc, char *line, int *fd);
bool			new_delimiter(t_data *data, t_redir_her *doc);
bool			read_heredoc(t_data *data, t_redir_her *doc, \
char *tmp, int *fd);
bool			history_heredoc(t_data *data, char *line, int *fd);

t_cmd			*new_cmd_node(t_data *data);
t_cmd			*parsing_commands(t_data *data, t_token *tokens);
t_token			*tokeniser(t_data *data, char *input);
t_token			*token_new(char *input, int len, int type, bool quot);
//======================================================//

//===================<for sig usage>===============//
void			handle_signal(int signal);
void			handle_heredoc(int signal);
int				rl_event(void);
//===============================================//

//===================a degager=====================//
void			display_env(t_env *view);// a degager a la fin
void			display_tokens(t_token *token);//
void			display_cmd(t_cmd *view);//
//===============================================//
#endif
