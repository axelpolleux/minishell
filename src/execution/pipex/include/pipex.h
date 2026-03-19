/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:18:24 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/16 10:16:57 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libftprintf.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>

//====================<for all struct>===================//

typedef struct s_data
{
	char		**path;
	char		**cmd_split;

	char		*path_and_cmd;
	char		*cmd_space_void;

	int			ac;
	int			fd_storage[2];
	int			cmd_null;
	int			cmd_invalid;
	int			path_invalid;
	int			path_void;
	int			path_null;

	pid_t		pid[2];

}				t_data;
//=======================================================//

//=================<for all type of error>================//
void			command_error(t_data *data);
void			null_command(t_data *data);
void			null_path(t_data *data);
void			void_path(t_data *data);

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

t_data			*init_data(void);
//======================================================//

//========================<for pipex>=========================//
char			**get_path(char **env, char *motif, t_data *data);

void			verif_command(t_data *d, char **env);
void			get_cmd_path(char *cmd, char **env, t_data *d);
void			command_1(char **av, char **env, t_data *d);
void			command_2(char **av, char **env, t_data *d);
void			process_manage(t_data *data, char **env, char **av);
void			cmd_whith_path(t_data *data, char *command);
void			full_cmd(t_data *data, char *command, int i);
void			exec_command(char **env, t_data *d);

int				verif_file(char *line, int in);
//===========================================================//

#endif