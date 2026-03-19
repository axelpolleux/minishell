/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:33:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/02 18:59:13 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>

void	ft_putstr(char *str, int *len);
void	ft_putnbr(long n, int *len);
void	ft_putchar(char c, int *len);
void	ft_putnbr_base(size_t nbr, char *base, int *len);
void	ft_verif_p(size_t nbr, char *base, int *len);
size_t	ft_strlen(const char *str);
int		ft_printf_2(const char *str, ...);

#endif