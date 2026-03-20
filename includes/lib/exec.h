/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:18:24 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/19 13:56:19 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

//========================<for exec>=========================//
char			**get_path(char **env, char *motif, t_data *data);

void			verif_command(t_data *d, char **env);
void			get_cmd_path(char *cmd, char **env, t_data *d);
void			children(t_data *data, char **av, char **env);
void			tennage(t_data *data, char **av);
void			process_manage(t_data *data, t_node *node, char **env, char **av);
void			cmd_whith_path(t_data *data, char *command);
void			full_cmd(t_data *data, char *command, int i);
void			exec_command(char **env, t_data *d);
void			parent(char **av, char **env, t_data *data);
void			here_doc_manage(t_data *data);

int				verif_file(char *line, int in, int doc);
//===========================================================//





#endif