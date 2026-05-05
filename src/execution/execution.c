/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 18:43:56 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//data->cmd->cmd ne fonctinera pas [0] = cmd
void	exec_command(t_data *data, char **env)
{
	if (execve(data->cmd->cmd_path, data->cmd->cmd, env) == -1)
	{
		free_arr(env);
		perror("minishell");
		if (errno == ENOENT)
			data->exit = 127;
		else if (errno == EACCES)
			data->exit = 126;
		else
			data->exit = 1;
		exit (data->exit);
	}
	free_arr(env);
	exit (data->exit);
}

void	children(t_data *data, t_cmd *cmd)
{
	char	**env;

	if (is_builtin(data->built_in, cmd->cmd[0]))
	{
		exec_built(data, cmd);
		return ;
	}
	if (get_cmd_path(data, cmd))
	{
		manage_redir(data, cmd);
		if (cmd->next)
		{
			if (dup2(data->fd_storage[1], STDOUT_FILENO) == -1)
				dup_error(data);
			close(data->fd_storage[1]);
		}
		env = tab_env(data->t_env, -1);
		if (!env)
			data_malloc_error(data);
		exec_command(data, env);
	}
	else
	{
		data->exit = 1;
		exit (data->exit);
	}
}

void	parent(t_data *data, t_cmd *cmd) //pas finis
{
	if (data->exit > -2)
		cmd->input = data->fd_storage[0];
	close(data->fd_storage[1]);
	if (data->last_fd != -1)
		close(data->last_fd);
	if (cmd->next)
	{
		close(data->fd_storage[1]);
		data->last_fd = data->fd_storage[0];
	}
	else
		close(data->fd_storage[0]);

	// if (data->last_fd != -1)
	// {
	// 	if (dup2(data->last_fd, STDIN_FILENO) == -1)
	// 		dup_error(data);
	// 	close(data->last_fd);
	// }
}

void	manage_process(t_data *data, t_cmd *cmd)
{
	data->last_fd = -1;
	while (cmd)
	{
		if (pipe(data->fd_storage) == -1)//a amelioer pour faire un semi heredoc pour pipe end
			pipe_error(data);//
		g_signal = fork();
		if (g_signal < 0)
			fork_error(data);
		if (g_signal == 0)
			children(data, cmd);
		else
			parent(data, cmd);
		cmd = cmd->next;
	}
}

void	wait_end(t_data *data)
{
	t_cmd	*tmp;
	int		error;
	int		size_c;

	tmp = data->cmd;
	size_c = ft_lstsize_c(tmp);
	while (size_c--)
	{
		if (waitpid(0, &error, 0) == g_signal)
		{
			if (WIFEXITED(error))
				data->exit = WEXITSTATUS(error);
		}
		tmp = tmp->next;
	}
}

int	exec(t_data *data) 	//le pid et desormer gerer avec la global

{
	t_cmd	*t_cmd;

	t_cmd = data->cmd;
	get_expand(data, t_cmd);
	if (is_builtin(data->built_in, t_cmd->cmd[0]) && !t_cmd->next)
	{
		exec_built(data, t_cmd);
		return	;
	}
	// manage_process(data, t_cmd);
	// wait_end(data);
}


// int	exec(t_data *data)
// {
// 	t_cmd	*t_cmd;
// 	int		count;

// 	t_cmd = data->cmd;
// 	count = nb_process(t_cmd);// = nombre de cmd ft_lstsize
// 	if (count == 0)
// 		return ;
// 	data->pid = ft_calloc(sizeof(pid_t), count); //statique on vas utiliser de manier plus fluide
// 	if (!data->pid)
// 		data_malloc_error(data);
// 	get_expand(data, t_cmd);
// 	if (is_builtin(data->built_in, t_cmd->cmd[0]) && !t_cmd->next)
// 	{
// 		exec_built(data, t_cmd);
// 		return (data->exit);
// 	}
// 	parent(data, t_cmd);
// 	wait_end(data);
// 	return (data->exit);
// }
