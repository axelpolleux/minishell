/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:43:02 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/01 19:09:56 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_command(t_data *data, char  **env)
// {
// 	if (execve(data->cmd->cmd_path, data->cmd->cmd, env) == -1)
// 	{
// 		free_arr(env);
// 		perror("minishell");
// 		free_data(data);
// 		if (errno == ENOENT)
// 			exit(127);
// 		else if (errno == EACCES)
// 			exit(126);
// 		else
// 			exit(1);
// 	}
// 	free_arr(env);
// }

// void manage_redir(t_cmd *cmd) // a revoir pas possible
// {
// 	if (!cmd->input)
// 	{
// 		dup2(cmd->input, STDIN_FILENO);
// 		close(cmd->input);
// 	}
// 	if (!cmd->output)
// 	{
// 		dup2(cmd->output, STDOUT_FILENO);
// 		close(cmd->output);
// 	}
// }

// void children(t_data *data, t_cmd *cmd)
// {
// 	char **env;

// 	if (data->last_fd != -1)
// 	{
// 		dup2(data->last_fd, STDIN_FILENO);
// 		close(data->last_fd);
// 	}
// 	if (cmd->next)
// 	{
// 		dup2(data->fd_storage[1], STDOUT_FILENO);
// 		closes(-1, data->fd_storage);
// 	}
// 	manage_redir(cmd);
// 	if (is_builtin(data->built_in, data->cmd->cmd[0]))
// 		exec_built(data, cmd);
// 	get_cmd_path(data);
// 	env = tab_env(data->t_env);
// 	if (!env)
// 		data_malloc_error(data);
// 	exec_command(data, env);
// }

// void parent(t_data *data, t_cmd *cmd, int i)
// {

// 	data->last_fd = -1;
// 	while (cmd)
// 	{
// 		data->fd_storage[0] = -1;
// 		data->fd_storage[1] = -1;
// 		if (cmd->next && pipe(data->fd_storage) == -1)
// 			pipe_error(data); 
// 		data->pid[i] = fork();
// 		if (data->pid[i] == 0)
// 			children(data, cmd);
// 		if (data->last_fd != -1)
// 			close(data->last_fd);
// 		if (cmd->next)
// 		{
// 			close(data->fd_storage[1]);
// 			data->last_fd = data->fd_storage[0];
// 		}
// 		cmd = cmd->next;
// 	}
// }

// void wait_end(t_data *data, int count)
// {
// 	int i;
// 	int error;

// 	i = 0;
// 	while (i < count)
// 	{
// 		waitpid(data->pid[i], &error, 0);
// 		i++;
// 	}
// 	free_data(data);
// 	if (WIFEXITED(error))
// 		exit(WEXITSTATUS(error));
// }

// void exec(t_data *data)
// {
// 	t_cmd *cmd;
// 	int count;

// 	cmd = data->cmd;
// 	count = nb_process(data->cmd);
// 	if (count == 0)
// 		return ;
// 	data->pid = ft_calloc(sizeof(pid_t), count);
// 	if (!data->pid)
// 		data_malloc_error(data);
// 	if (is_builtin(data->built_in, data->cmd->cmd[0]) && !data->cmd->next) // si une seule commande et built
// 		exec_built(data, cmd);
// 	else
// 		parent(data, cmd, -1);
// 	wait_end(data, count);
// }

void manage_redir(t_data *data, t_cmd *cmd)
{
	if (cmd->input != -1)
	{
		if (dup2(cmd->input, STDIN_FILENO) == -1)
			dup_error(data);
		close(cmd->input);
	}
	if (cmd->output != -1)
	{
		if (dup2(cmd->output, STDOUT_FILENO) == -1)
			dup_error(data);		
		close(cmd->output);
	}
}

void exec_command(t_data *data)
{
	char **env;
	
	env = tab_env(data->t_env);
	if (!env)
		data_malloc_error(data);
	if(execve(data->cmd->cmd_path, data->cmd->cmd, env) == -1)
	{
		free_arr(env);
		perror("minishell");
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(1);
	}
	free_arr(env);
}

void children(t_data *data, t_cmd *cmd)
{
	if (data->last_fd != -1)
	{
		if (dup2(data->last_fd, STDIN_FILENO) == -1)
			dup_error(data);
		close(data->last_fd);
	}
	if (cmd->next)
	{
		if (dup2(data->fd_storage[1], STDOUT_FILENO) == -1)
			dup_error(data);
		closes(-1, data->fd_storage);
	}
	manage_redir(data, cmd);
	if (is_builtin(data->built_in, cmd->cmd[0]))
	{
		//exec_built(data, cmd);
		free_data(data);
		exit(0);
	}
	get_cmd_path(data);
	exec_command(data);
}

void parent(t_data *data, t_cmd *cmd)
{
	int	i;

	data->last_fd = -1;
	i = 0;
	while (cmd)
	{
		if (cmd->next && pipe(data->fd_storage) == -1)
			pipe_error(data);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			pipe_error(data);
		if (data->pid[i] == 0)
			children(data, cmd);
		if (data->last_fd != -1)
			close(data->last_fd);
		if (cmd->next)
		{
			close(data->fd_storage[1]);
			data->last_fd = data->fd_storage[0];
		}
		cmd = cmd->next;
		i++;
	}
}

void wait_end(t_data *data, int count)
{
	int i;
	int status;

	i = -1;
	while (++i < count)
		if (waitpid(data->pid[i], &status, 0) == -1)
			wait_error(data);
	free_data(data);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

void exec(t_data *data)
{
	t_cmd *cmd;
	int count;

	cmd = data->cmd;
	count = nb_process(cmd);
	if (count == 0)
		return ;
	data->pid = ft_calloc(sizeof(pid_t), count);
	if (!data->pid)
		data_malloc_error(data);
	// if (is_builtin(data->built_in, cmd->cmd[0]) && !cmd->next)
	// 	exec_built(data, cmd);
	parent(data, cmd);
	wait_end(data, count);
}

/*
		/`·.¸
	   /¸...¸`:·
   ¸.·´  ¸   `·.¸.·´)
  : © ):´;      ¸  {
   `·.¸ `·  ¸.·´\`·¸)
	   `\\´´\¸.·´





						 _.'.__
					  _.'      .
':'.               .''   __ __  .
  '.:._          ./  _ ''     "-'.__
.'''-: """-._    | .                "-"._
 '.     .    "._.'                       "
	'.   "-.___ .        .'          .  :o'.
	  |   .----  .      .           .'     (
	   '|  ----. '   ,.._                _-'
		.' .---  |.""  .-:;.. _____.----'
		|   .-""""    |      '
	  .'  _'         .'    _'
	 |_.-'            '-.'


		/`·.¸
	   /¸...¸`:·
   ¸.·´  ¸   `·.¸.·´)
  : © ):´;      ¸  {
   `·.¸ `·  ¸.·´\`·¸)
	   `\\´´\¸.·´

	   

		/`·.¸
	   /¸...¸`:·
   ¸.·´  ¸   `·.¸.·´)
  : © ):´;      ¸  {
   `·.¸ `·  ¸.·´\`·¸)
	   `\\´´\¸.·´

*/