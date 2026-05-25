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
		printf("============================\n");
		printf("cmd => {");
		while (view->cmd[++i])
		{
			printf("%s", view->cmd[i]);
			if (view->cmd[i + 1])
				printf(", ");
		}
		printf("}\n");
		printf("cmd_path => %s\n", view->cmd_path);
		printf("full_cmd => %s\n", view->full_cmd);
		printf("input => %d\n", view->input);
		printf("output => %d\n", view->output);
		view = view->next;
	}
}

//=======a degager a la fin==========//

// //pour voir l'historique
// HIST_ENTRY **history;
// history = history_list();
// int i = -1;
// while (history[++i])
//     printf("=> %s\n", history[i]->line);
//=======================================//

// void	display_tokens(t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token)
// 	{
// 		printf("%d: {%s - %d}\n", i, token->cmd, token->type);
// 		i++;
// 		token = token->next;
// 	}
// }

