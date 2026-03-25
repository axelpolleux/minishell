/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:53:00 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/25 17:42:03 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=======a degager a la fin==========//
void	display_env(t_env *view)
{
	int	i;

	i = 0;
	while (view)
	{
		printf("->%s \n", view->var);
		view = view->next;
	}
}

void	display_token(t_token *view)
{
	int	i;

	i = 0;
	while (view)
	{
		printf("============================\n");
		printf("token => {%s}\n", view->cmd);
		view = view->next;
	}
}
// void display_cmd(t_token *view)
// {
// 	int	i;

// 	i = 0;
// 	while (view)
// 	{
// 		printf("============================\n");
// 		printf("token => {%s}\n", view->cmd);
// 		view = view->next;
// 	}
// }

//=======================================//

// void	get_new(int i, char *line, char **env, t_data *data)
// {
// 	t_env	*new;

// 	while (env[i])
// 	{
// 		line = ft_strdup(env[i]);
// 		if (!line)
// 			data_malloc_error(data);
// 		new = new_env(line);
// 		if (!new)
// 		{
// 			free(line);
// 			data_malloc_error(data);
// 		}
// 		add_to_bottom(&data->env, new);
// 		i++;
// 	}
// }

// int	get_env(t_data *data, char **env)
// {
// 	t_env	*tmp;
// 	char	*line;

// 	if (!env || !(*env)) // a reconstruire ?    oui imperativement
// 	{
// 		//make_env(t_data *data);
// 		free_data(data);
// 		exit (0);
// 	}
// 	line = ft_strdup(env[0]);
// 	if (!line)
// 		data_malloc_error(data);
// 	tmp = new_env(line);
// 	if (!tmp)
// 	{
// 		free(line);
// 		data_malloc_error(data);
// 	}
// 	data->env = tmp;
// 	get_new(1, line, env, data);
// 	return (1);
// }

int	exit_shell(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	if (line && *line)
		add_history(line);
	if (!strcmp(line, "exit"))
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_data	*data;

// 	data = init_data(ac, av);
// 	get_env(data, env);
// 	//export_central(data);
// 	//display_env(data->env);
// 	while (1)
// 	{
// 		data->line = readline("mimishell> ");
// 		if (exit_shell(data->line))
// 			break ;
// 		tokenization(data);
// 		//exec(data);
// 	}
// 	rl_clear_history();
// 	free_data(data);
// 	return (0);
// }



int	main(void)
{
	char *line;
	char **word;
    int i;

	while (1)
	{
		line = readline("mimishell> ");
		if (exit_shell(line))
			break ;
		word = token_slpit(line);
		i = -1;
		while (word[++i])
			printf("%d -> {%s}\n", i + 1, word[i]);
    	free_arr(word);
		free(line);
	}
	rl_clear_history();
	return (0);
}






/*
Cheer up, Brian
You know what they say…

Some things in life are bad
They can really make you mad
Other things just make you swear and curse
When you’re chewing on life’s gristle
Don’t grumble, give a whistle
And this’ll help things turn out for the best

And always look on the bright side of life
Always look on the light side of life

If life seems jolly rotten
There’s something you’ve forgotten
And that’s to laugh and smile and dance and sing
When you’re feeling in the dumps
Don’t be silly chumps
Just purse your lips and whistle, that’s the thing

And always look on the bright side of life
Come on!
Always look on the right side of life

For life is quite absurd
And death’s the final word
You must always face the curtain with a bow
Forget about your sin
Give the audience a grin
Enjoy it, it’s your last chance anyhow

So, always look on the bright side of death
A-just before you draw your terminal breath

Life’s a piece of shit
When you look at it
Life’s a laugh and death’s a joke, it’s true
You’ll see it’s all a show
Keep ’em laughing as you go
Just remember that the last laugh is on you

And always look on the bright side of life
Always look on the right side of life

C’mon Brian, cheer up!

Always look on the bright side of life
Always look on the bright side of life

Worse things happen at sea, you know
Always look on the bright side of life

I mean, what have you got to lose
You know, you come from nothing, you’re going back to nothing
What have you lost? Nothing!

Always look on the right side of life…

Nothing will come from nothing, you know what they say?
Cheer up you old bugger, c’mon give us a grin!
There you are, see, it’s the end of the film
Incidentally, this record is available in the foyer
Some of us have to got live as well, you know
Who do you think pays for all this rubbish
They’re not gonna make their money back, you know
I told them, I said to them, Bernie, I said they’ll never make their money back
*/