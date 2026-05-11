/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/11 10:21:31 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_data *data, t_cmd *cmd, char **env)
{
	//display_cmd(data->cmd);
	// int i = -1;
	// while (env[++i])
	// 	printf("%s\n", env[i]);
	if (execve(cmd->cmd_path, cmd->cmd, env) == -1)
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

}

void	children(t_data *data, t_cmd *cmd)
{
	char	**env;

	if (is_builtin(data->built_in, cmd->cmd[0]))
		built_child(data, cmd);
	else if (!check_cmd(data, cmd))
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
		exec_command(data, cmd, env);
	}
	exit(data->exit);
}

void	parent(t_data *data, t_cmd *cmd) //pas finis
{
	if (data->flag)
		cmd->input = data->fd_storage[0];
	else 
		data->flag = 1;
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
}

void	manage_process(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	data->last_fd = -1;
	while (cmd)
	{
		if (data->pipe-- > 0)
			if (pipe(data->fd_storage) == -1)
				pipe_error(data);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			fork_error(data);
		else if (data->pid[i] == 0)
			children(data, cmd);
		else
			parent(data, cmd);
		cmd = cmd->next;
		i++;
	}
}

void	wait_end(t_data *data, int count)
{
	int	i;
	int	error;

	i = -1;
	while (++i < count)
		if (waitpid(data->pid[i], &error, 0) == -1)
			wait_error(data);
	if (WIFEXITED(error))
		data->exit = (WEXITSTATUS(error));
	free(data->pid);
	data->pid = NULL;
}

int	exec(t_data *data)
{
	t_cmd	*t_cmd;
	int		count;

	t_cmd = data->cmd;
	get_expand(data, t_cmd);
	if (is_builtin(data->built_in, t_cmd->cmd[0]) && !t_cmd->next)
	{
		exec_built(data, t_cmd);
		return	;
	}
	count = ft_lstsize_c(t_cmd);
	data->pid = ft_calloc(sizeof(pid_t), count);
	if (!data->pid)
		data_malloc_error(data);
	manage_process(data, t_cmd);
	wait_end(data, count);
}


// void	wait_end(t_data *data)
// {
// 	t_cmd	*tmp;
// 	int		error;
// 	int		size_c;

// 	tmp = data->cmd;
// 	size_c = ft_lstsize_c(tmp);
// 	while (size_c--)
// 	{
// 		if (waitpid(0, &error, 0) == g_signal)
// 		{
// 			if (WIFEXITED(error))
// 				data->exit = WEXITSTATUS(error);
// 		}
// 		tmp = tmp->next;
// 	}
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
