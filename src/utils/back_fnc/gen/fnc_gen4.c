/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnc_gen4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:43:28 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/05 17:49:37 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_upd(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	if (!str)
		return (NULL);
	return (str);
}

int	word_size(char *str, char charset)
{
	int	i;

	i = 0;
	while (*str && *str != charset)
	{
		i++;
		str++;
	}
	return (i);
}

int	key_in_env(t_data *data, char *key)
{
	t_env	*env;
	int		i;

	env = data->t_env;
	i = 0;
	while (env)
	{
		if (!strcmp(key, env->key))
			return (1);
		env = env->next;
	}
	return (0);
}

int	only_key(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	only_key_equal(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=' && line[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}
