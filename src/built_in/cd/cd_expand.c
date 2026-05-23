/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:includes/libft/ft_free_arr.c
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:39:21 by ethutin-          #+#    #+#             */
/*   Updated: 2026/04/16 14:40:40 by ethutin-         ###   ########.fr       */
========
/*   cd_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:50:48 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/06 12:51:17 by ethutin-         ###   ########.fr       */
>>>>>>>> refs/heads/exec:src/built_in/cd/cd_expand.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<<< HEAD:includes/libft/ft_free_arr.c
void	*free_arr(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
========
int	update_cd(t_data *data, char *new_var, char *new_key, char *new_arg)
{
	t_env	*tmp;

	tmp = data->t_env;
	while (tmp)
	{
		if (!ft_strcmp(new_key, tmp->key))
		{
			if (tmp->var)
				free(tmp->var);
			if (tmp->arg)
				free(tmp->arg);
			if (tmp->key)
				free(tmp->key);
			tmp->var = new_var;
			tmp->arg = new_arg;
			tmp->key = new_key;
			tmp->export = 1;
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
>>>>>>>> refs/heads/exec:src/built_in/cd/cd_expand.c
}
