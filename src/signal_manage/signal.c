/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:23:20 by ethutin-          #+#    #+#             */
/*   Updated: 2026/05/01 15:13:56 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//volatile sig_atomic_t	g_signal;

// int	does_errexist(void)
// {
// 	char	*str;
// 	int		err;

// 	str = ft_searchsterr();
// 	if (!str)
// 		err = 0;
// 	else
// 		err = ft_atoi(str);
// 	free(str);
// 	return (err);
// }

// void	ft_signal_d(t_env *env)
// {
// 	int	err;

// 	err = does_errexist();
// 	free_env(env);
// 	ft_putendl_fd("exit", 2);
// 	rl_clear_history();
// 	exit(err);
// }

// void	ft_sigint_heredoc(int pid)
// {
// 	signal(pid, SIG_IGN);
// 	signal(SIGINT, SIG_DFL);
// 	g_signal = SIGINT;
// }

// void	ft_sigint_cmd(int pid)
// {
// 	(void) pid;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	error_signal(SIGINT);
// 	signal(SIGINT, signal_manage);
// }

// void	signal_manage(int pid)
// {
// 	(void) pid;
// 	signal(SIGINT, SIG_IGN);
// 	if (g_signal == SIGINT)
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		return ;
// 	}
// 	g_signal = 0;
// 	error_signal(SIGINT);
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	rl_redisplay();
// 	signal(SIGINT, signal_manage);
// }











// char	*ft_searchsterr(void)
// {
// 	int		fd;
// 	int		i;
// 	char	*buf;

// 	fd = open("/tmp/.$?", O_RDONLY);
// 	if (fd == -1)
// 		return (ft_strdup("0"));
// 	else
// 	{
// 		buf = malloc(sizeof(char) * BUFFER_SIZE);
// 		if (!buf)
// 			return (ft_strdup("12"));
// 		i = read(fd, buf, BUFFER_SIZE);
// 		if (i == -1)
// 			return (NULL);
// 		close(fd);
// 		buf[i] = '\0';
// 		unlink("/tmp/.$?");
// 		return (buf);
// 	}
// }

// char	*ft_switch(char *str, int start)
// {
// 	char	*sterr;
// 	char	*tmp;
// 	char	*tmp2;

// 	tmp = ft_betterdup(str, start + 2, ft_strlen(str));
// 	tmp2 = ft_betterdup(str, 0, start);
// 	free (str);
// 	sterr = ft_searchsterr();
// 	if (!tmp || !tmp2 || !sterr)
// 		return (NULL);
// 	str = ft_strjoin(tmp2, sterr);
// 	free(tmp2);
// 	free(sterr);
// 	tmp2 = ft_strjoin(str, tmp);
// 	if (!tmp2 || !str)
// 		return (NULL);
// 	free(tmp);
// 	free(str);
// 	return (tmp2);
// }

// char	*ft_statuserr(char *str)
// {
// 	int	occ;
// 	int	i;

// 	i = 0;
// 	occ = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 34 && occ == 0)
// 			occ = -1;
// 		else if (str[i] == 39 && occ == 0)
// 			occ = 1;
// 		if (str[i] == '$' && str[i + 1] == '?' && occ != 1)
// 		{
// 			str = ft_switch(str, i);
// 			if (!str)
// 				return (NULL);
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (str);
// }

