/*char *handle_dollar(char *line, char *res, t_data *data, int *i)
{
	char var_name[256];
	int j = 0;

	while (ft_isalnum(line[j]) || line[j] == '_')
	{
		var_name[j] = line[j];
		j++;
	}
	var_name[j] = '\0';

	char *value = get_env(data, var_name);
	if (value)
		res = append_str(res, value);

	*i += j - 1;
	return res;
}



char *expand(char *line, t_data *data)
{
	int i = 0;
	t_quote quote = NO_QUOTE;
	char *result = ft_strdup("");

	while (line[i])
	{
		// gérer les quotes
		if (line[i] == '\'' && quote == NO_QUOTE)
			quote = SINGLE_QUOTE;
		else if (line[i] == '\'' && quote == SINGLE_QUOTE)
			quote = NO_QUOTE;
		else if (line[i] == '"' && quote == NO_QUOTE)
			quote = DOUBLE_QUOTE;
		else if (line[i] == '"' && quote == DOUBLE_QUOTE)
			quote = NO_QUOTE;

		// expansion $
		else if (line[i] == '$' && quote != SINGLE_QUOTE)
		{
			i++;
			result = handle_dollar(&line[i], result, data, &i);
			continue;
		}
		else
		{
			result = append_char(result, line[i]);
		}
		i++;
	}
	return result;
}

char	*append_char(char *str, char c)
{
	char	*new;
	int		len;

	len = str ? ft_strlen(str) : 0;
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	if (str)
		ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}

char	*append_str(char *str, char *add)
{
	char	*new;
	int		len1;
	int		len2;

	if (!add)
		return (str);
	len1 = str ? ft_strlen(str) : 0;
	len2 = ft_strlen(add);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	if (str)
		ft_memcpy(new, str, len1);
	ft_memcpy(new + len1, add, len2);
	new[len1 + len2] = '\0';
	free(str);
	return (new);
}






char	*get_env_value(t_data *data, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], key, len)
			&& data->env[i][len] == '=')
			return (data->env[i] + len + 1);
		i++;
	}
	return (""); // bash retourne vide si non trouvé
}






int	get_var_name(char *line, char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(line[i]) && line[i] != '_')
		return (0);
	while (ft_isalnum(line[i]) || line[i] == '_')
	{
		name[i] = line[i];
		i++;
	}
	name[i] = '\0';
	return (i);
}






char	*handle_dollar(char *line, int *i, char *res, t_data *data)
{
	char	var[256];
	int		len;
	char	*value;

	// cas spécial: $?
	if (line[*i] == '?')
	{
		res = append_str(res, ft_itoa(data->last_exit));
		(*i)++;
		return (res);
	}

	len = get_var_name(&line[*i], var);
	if (len == 0)
		return (append_char(res, '$'));

	value = get_env_value(data, var);
	res = append_str(res, value);
	*i += len;
	return (res);
}





char	*line_expand(char *line, t_data *data)
{
	int		i;
	t_quote	quote;
	char	*res;

	i = 0;
	quote = NO_QUOTE;
	res = ft_strdup("");

	while (line[i])
	{
		// gestion des quotes
		if (line[i] == '\'' && quote == NO_QUOTE)
			quote = SINGLE_QUOTE;
		else if (line[i] == '\'' && quote == SINGLE_QUOTE)
			quote = NO_QUOTE;
		else if (line[i] == '"' && quote == NO_QUOTE)
			quote = DOUBLE_QUOTE;
		else if (line[i] == '"' && quote == DOUBLE_QUOTE)
			quote = NO_QUOTE;

		// expansion
		else if (line[i] == '$' && quote != SINGLE_QUOTE)
		{
			i++;
			res = handle_dollar(line, &i, res, data);
			continue;
		}
		else
			res = append_char(res, line[i]);

		i++;
	}
	return (res);
}


int	expand_cmd(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*new;

	i = 0;
	while (cmd->cmd[i])
	{
		new = line_expand(cmd->cmd[i], data);
		if (!new)
			return (EXIT_FAILURE);
		free(cmd->cmd[i]);
		cmd->cmd[i] = new;
		i++;
	}
	return (EXIT_SUCCESS);
}

*/