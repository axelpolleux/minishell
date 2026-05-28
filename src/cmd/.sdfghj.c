
// // bool syntax_error(t_token *token);

// t_cmd	*parsing_commands(t_data *data, t_token *token)
// {
// 	t_cmd	*head;
// 	t_cmd	*cmd;

// 	head = new_cmd_node(data);
// 	if (!head)
// 		return (NULL);
// 	cmd = head;
// 	while (token)
// 	{
// 		if (token->type == WORD)
// 		{
// 			if (tok_to_cmd(data, cmd, token->cmd))
// 				return (free_cmd(head), NULL);
// 		}
// 		else if (is_redir(token->type))
// 		{
// 			if (!token->next || token->next->type != WORD)
// 			{
// 				ft_putstr_fd(SYNT_NR, 2);
// 				data->exit = 2;
// 				return (free_cmd(head), NULL);
// 			}
// 			if (new_redirection(data, cmd,
// 					token->type,
// 					token->next->cmd))
// 				return (free_cmd(head), NULL);
// 			token = token->next;
// 		}
// 		else if (token->type == PIPE)
// 		{
// 			if (!token->next)
// 			{
// 				ft_putstr_fd(SYNT_NR, 2);
// 				data->exit = 2;
// 				return (free_cmd(head), NULL);
// 			}
// 			cmd->next = new_cmd_node(data);
// 			if (!cmd->next)
// 				return (free_cmd(head), NULL);
// 			cmd->next->prev = cmd;
// 			cmd = cmd->next;
// 		}
// 		token = token->next;
// 	}
// 	return (head);
// }


// t_cmd	*parsing_commands(t_data *data, t_token *token)
// {
// 	t_cmd	*new;
// 	t_cmd	*cmd;

// 	new = new_cmd_node(data);
// 	if (!new)
// 		return (NULL);

// 	cmd = new;

// 	while (token)
// 	{
// 		if (token->type == WORD)
// 		{
// 			if (tok_to_cmd(data, cmd, token->cmd))
// 				return (free_cmd(new), NULL);
// 		}
// 		else if (is_redir(token->type))
// 		{
// 			if (parse_redir(data, &token, cmd))
// 				return (free_cmd(new), NULL);
// 		}
// 		else if (new_cmd(data, &cmd, token->type))
// 		{
// 			free_cmd(new);
// 			return (NULL);
// 		}

// 		token = token->next;
// 	}

// 	return (new);
// }



/*

bool	double_quotes(char *input, int index)
{
	int		i;

	if (input[index] != '\"')
		return (true);
	i = 1;
	while (input[index + i] && input[index + i] != '\"')
		i++;
	if (!input[index + i])
		return (error_pars());
	return (false);
}

bool	single_quotes(char *input, int index)
{
	int		i;

	if (input[index] != '\'')
		return (true);
	i = 1;
	while (input[index + i] && input[index + i] != '\'')
		i++;
	if (!input[index + i])
		return (error_pars());
	return (false);
}

bool	not_valid_quote(char *input)
{
	int index;

	index = -1;
	while (input[++index])
	{
		if (input[index] == '"')
		{
			if (double_quotes(input, index))
				return (true);
		}
		else if (input[index] == '\'')
		{
			if (single_quotes(input, index))
				return (true);
		}
	}
	return (false);
}



bool    syntax_error(t_data *data, t_token *token)
{
	t_token	*tmp;

	(void)data;
	tmp = token;
	while (tmp)
	{
		if (not_valid_quote(tmp->cmd))
			return (EXIT_FAILURE);
		return (true);
	// if (pipe_pars(data, tok))
	// 	return (true);
	tmp = tmp->next;
	}
	return (false);
}




*/




















/*
t_cmd	*new_cmd_node(t_data *data)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
	{
		data->exit = -2;
		return (NULL);
	}
	new->input = -1;
	new->output = -1;
	return (new);
}
*/






// t_redir_her	*new_redirection(int type, char *file)
// {
// 	t_redir_her	*new;

// 	new = ft_calloc(sizeof(t_redir_her), 1);
// 	if (!new)
// 		return (NULL);
// 	new->type = type;
// 	new->file = ft_strdup(file);
// 	if (!new->file)
// 	{
// 		free(new);
// 		return (NULL);
// 	}
// 	new->fd = -1;
// 	return (new);
// }


// int	tok_start(t_cmd *new, t_token *start, t_cmd **cmds)
// {
// 	if (start)
// 	{
// 		new = new_cmd_node();
// 		if (!new)
// 		{
// 			free_cmd(*cmds);
// 			return (EXIT_FAILURE);
// 		}
// 		new->cmd = tokens_to_argv(start, NULL, 0);
// 		if (!new->cmd)
// 		{
// 			free(new);
// 			free_cmd(*cmds);
// 			return (EXIT_FAILURE);
// 		}
// 		if (parse_redir(new, start, NULL))
// 		{
// 			free_cmd(new);
// 			free_cmd(*cmds);
// 			return (EXIT_FAILURE);
// 		}
// 		add_cmd_back(cmds, new);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	tok_to_cmd(t_token *token, t_cmd *new, t_token **start, t_cmd **cmds)
// {
// 	if (token->type == PIPE)
// 	{
// 		new = new_cmd_node();
// 		if (!new)
// 		{
// 			free_cmd(*cmds);
// 			return (EXIT_FAILURE);
// 		}
// 		new->cmd = tokens_to_argv(*start, token, 0);
// 		if (!new->cmd)
// 		{
// 			free(new);
// 			free_cmd(*cmds);
// 			return (EXIT_FAILURE);
// 		}
// 		if (parse_redir(new, *start, token))
// 		{
// 			free_cmd(new);
// 			free_cmd(*cmds);
// 			return (EXIT_FAILURE);
// 		}
// 		add_cmd_back(cmds, new);
// 		*start = token->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

// t_cmd	*parse_commands(t_token *token)
// {
// 	t_cmd	*cmds;
// 	t_cmd	*new;
// 	t_token	*start;

// 	cmds = NULL;
// 	new = NULL;
// 	start = token;
// 	while (token)
// 	{
// 		if (tok_to_cmd(token, new, &start, &cmds))
// 			return (NULL);
// 		token = token->next;
// 	}
// 	if (tok_start(new, start, &cmds))
// 		return (NULL);
// 	return (cmds);
// }








// Ton parser actuel ne détecte PAS :

// | ls
// ls ||
// echo >

// Il faudrait ajouter une validation syntaxique AVANT parsing.

// Typiquement :

// bool syntax_error(t_token *token);

// Sinon tu vas avoir :

// segfaults
// commandes vides
// mauvais AST