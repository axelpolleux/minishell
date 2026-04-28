/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:04:56 by apolleux          #+#    #+#             */
/*   Updated: 2026/04/28 19:16:19 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	main_reading(t_data *data, char *title)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		data->line = readline(title);
		if (!data->line)
		{
			free_data(data);
			printf("exit\n");
			exit(0);
		}
		if (!strcmp(data->line, "exit"))// temporaire a degager
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (data->line && *(data->line) && !full_void(data->line))
			add_history(data->line);
//=====================================================//
		char	**ar_tmp;
		char	**tmp;
		int		i = -1;

		ar_tmp = ft_split(data->line, '@'); // cractere speciale pour teste les space
		if (!ar_tmp)
			data_malloc_error(data);
		tmp = get_expand_t(data, ar_tmp); // pour teste
		if (!tmp)
		{
			free_arr(ar_tmp);
			data_malloc_error (data);
		}
		i = -1;
		while (tmp[++i])
			printf("arg_cmd:%d:{%s}\n", i + 1, tmp[i]);
		free_arr(ar_tmp);
		free_arr(tmp);
//=====================================================//
		main_parser(data);
		exec(data);
	}
	clear_history();
}
