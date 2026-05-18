/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:10:40 by apolleux          #+#    #+#             */
/*   Updated: 2026/05/15 14:40:08 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_her	*new_redirection(int type, char *file)
{
	t_redir_her	*new;

	new = ft_calloc(1, sizeof(t_redir_her));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = ft_strdup(file);
	if (!new->file)
	{
		free(new);
		return (NULL);
	}
	new->fd = -1;
	return (new);
}

int	parse_redirections(t_cmd *cmd, t_token *tok, t_token *end)
{
	t_redir_her	*new;

	while (tok && tok != end)
	{
		if (is_redir(tok->type))
		{
			if (!tok->next || tok->next->type != WORD)
			{
				ft_putstr_fd("syntax error near redirection\n", 2);
				return (EXIT_FAILURE);
			}
			new = new_redirection(tok->type, tok->next->cmd);
			if (!new)
				return (EXIT_FAILURE);
			add_redir_back(&cmd->redir, new);
			tok = tok->next;
		}
		tok = tok->next;
	}
	return (0);
}

int	tok_start(t_cmd *new, t_token *start, t_cmd **cmds)
{
	if (start)
	{
		new = new_cmd_node();
		if (!new)
		{
			free_cmd(*cmds);
			return (EXIT_FAILURE);
		}
		new->cmd = tokens_to_argv(start, NULL, 0);
		if (!new->cmd)
		{
			free(new);
			free_cmd(*cmds);
			return (EXIT_FAILURE);
		}
		if (parse_redirections(new, start, NULL))
		{
			free_cmd(new);
			free_cmd(*cmds);
			return (EXIT_FAILURE);
		}
		add_cmd_back(cmds, new);
	}
	return (EXIT_SUCCESS);
}

int	tok_to_cmd(t_token *token, t_cmd *new, t_token **start, t_cmd **cmds)
{
	if (token->type == PIPE)
	{
		new = new_cmd_node();
		if (!new)
		{
			free_cmd(*cmds);
			return (EXIT_FAILURE);
		}
		new->cmd = tokens_to_argv(*start, token, 0);
		if (!new->cmd)
		{
			free(new);
			free_cmd(*cmds);
			return (EXIT_FAILURE);
		}
		if (parse_redirections(new, *start, token))
		{
			free_cmd(new);
			free_cmd(*cmds);
			return (EXIT_FAILURE);
		}
		add_cmd_back(cmds, new);
		*start = token->next;
	}
	return (EXIT_SUCCESS);
}

t_cmd	*parse_commands(t_token *token)
{
	t_cmd	*cmds;
	t_cmd	*new;
	t_token	*start;

	cmds = NULL;
	new = NULL;
	start = token;
	while (token)
	{
		if (tok_to_cmd(token, new, &start, &cmds))
			return (NULL);
		token = token->next;
	}
	if (tok_start(new, start, &cmds))
		return (NULL);
	return (cmds);
}
