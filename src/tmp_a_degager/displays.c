/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:48:50 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/28 11:41:20 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_env *view)
{
	while (view)
	{
		printf("var-> %s \n", view->var);
		printf("arg-> %s \n", view->arg);
		printf("key-> %s \n", view->key);
		printf("export-> %d \n", view->export);
		printf("====================\n");
		view = view->next;
	}
}

void	display_cmd(t_cmd *view)
{
	int	i;

	while (view)
	{
		i = -1;
		printf("============================\ncmd => {");
		while (view->args[++i])
		{
			printf("%s", view->args[i]);
			if (view->args[i + 1])
				printf(", ");
		}
		printf("}\ncmd_path => %s\n", view->cmd_path);
		printf("full_cmd => %s\n", view->full_cmd);
		printf("input => %d\n", view->input);
		printf("output => %d\n", view->output);
		view = view->next;
	}
}

void	display_tokens(t_token *view)
{
	int	i;

	i = 1;
	printf("nb_token:cmd:type:quoted\n");
	printf("{");
	while (view)
	{
		printf("%d:%s:%d", i, view->cmd, view->type);
		if (view->quot)
			printf(":1");
		else
			printf(":0");
		if (view->next)
			printf(", ");
		view = view->next;
		i++;
	}
	printf("}\n");
}
