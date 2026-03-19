/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:47:16 by ethutin-          #+#    #+#             */
/*   Updated: 2026/03/03 09:39:38 by ethutin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	control(char crt, va_list list, int *print_len)
{
	if (crt == 'd' || crt == 'i')
		ft_putnbr(va_arg(list, int), print_len);
	else if (crt == 'u')
		ft_putnbr(va_arg(list, unsigned int), print_len);
	else if (crt == 'c')
		ft_putchar(va_arg(list, int), print_len);
	else if (crt == 's')
		ft_putstr(va_arg(list, char *), print_len);
	else if (crt == 'p')
		ft_verif_p((size_t)va_arg(list, void *),
			"0123456789abcdef", print_len);
	else if (crt == 'x')
		ft_putnbr_base(va_arg(list, unsigned int),
			"0123456789abcdef", print_len);
	else if (crt == 'X')
		ft_putnbr_base(va_arg(list, unsigned int),
			"0123456789ABCDEF", print_len);
	else if (crt == '%')
		ft_putchar('%', print_len);
}

int	ft_printf_2(const char *str, ...)
{
	va_list	list;
	int		print_len;
	int		i;

	if (!str)
		return (-1);
	va_start(list, str);
	i = -1;
	print_len = 0;
	while (str[++i])
		if (str[i] == '%' && str[i + 1] == '\0' && str[i - 1] != '%')
			return (-1);
	while (*str)
	{
		if (*str != '%')
			ft_putchar(*str, &print_len);
		else
			control(*++str, list, &print_len);
		str++;
	}
	va_end(list);
	return (print_len);
}
