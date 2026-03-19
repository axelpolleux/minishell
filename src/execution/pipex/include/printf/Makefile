# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/25 11:30:58 by ethutin-          #+#    #+#              #
#    Updated: 2026/03/02 18:59:13 by ethutin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a


SRCS = ft_printf_2.c ft_putchar.c ft_verif_p.c \
		ft_putnbr_base.c ft_putnbr.c ft_putstr.c \
		ft_strlen.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all : $(NAME)
$(NAME) : $(OBJS)
	ar -crs $(NAME) $(OBJS)

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@
	
clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY:	all clean fclean re 
