/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:10:40 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/27 15:12:12 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	new_cmd(t_data *data, t_cmd **cmd, t_token *token)
{
	t_cmd	*new;

	if (token->type != PIPE)
		return (false);
	if (!token->next)
		return (error_pars(1));
	if (!(*cmd)->args && !(*cmd)->redir)
		return (error_pars(1));
	new = new_cmd_node(data);
	if (!new)
		return (true);
	(*cmd)->next = new;
	new->prev = *cmd;
	*cmd = new;
	return (false);
}

int	parse_redir(t_data *data, t_token **token, t_cmd *cmd)
{
	if (!(*token)->next || (*token)->next->type != WORD)
		return (error_pars(2));
	if (new_redirection(data, cmd, (*token)->type, (*token)->next->cmd))
		return (EXIT_FAILURE);
	*token = (*token)->next;
	return (0);
}

int	tok_to_cmd(t_data *data, t_cmd *cmd, char *str, int i)
{
	char	**new_args;

	while (cmd->args && cmd->args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i + 2);
	if (!new_args)
		return (EXIT_FAILURE);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(str);
	if (!new_args[i])
	{
		free_arr(new_args);
		data->exit = -2;
		return (EXIT_FAILURE);
	}
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (EXIT_SUCCESS);
}

t_cmd	*parsing_commands(t_data *data, t_token *token)
{
	t_cmd	*new;
	t_cmd	*cmd;

	new = new_cmd_node(data);
	if (!new)
		return (NULL);
	cmd = new;
	while (token)
	{
		if (token->type == WORD)
		{
			if (tok_to_cmd(data, cmd, token->cmd, 0))
				return (free_cmd(new), NULL);
		}
		else if (is_redir(token->type) && parse_redir(data, &token, cmd))
			return (free_cmd(new), NULL);
		else if (new_cmd(data, &cmd, token))
		{
			free_cmd(new);
			return (NULL);
		}
		token = token->next;
	}
	return (new);
}
