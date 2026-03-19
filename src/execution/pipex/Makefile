# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 11:14:39 by ethutin-          #+#    #+#              #
#    Updated: 2026/03/16 09:02:31 by ethutin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAMEB = pipex_bonus

INCLUDES = -Iinclude -Iinclude/printf

PRINTF_DIR = include/printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c pipex.c src/pipex_utils/central_pipex.c src/pipex_utils/pipex_extend_1.c \
	   src/utils/back_fnct/fnc_gen1.c src/utils/back_fnct/fnc_gen2.c \
	   src/utils/back_fnct/ft_split.c \
	   src/utils/manage_error/error1.c src/utils/manage_error/error2.c

SRCSB = bonus/main.c bonus/pipex.c bonus/src/pipex_utils/central_pipex.c bonus/src/pipex_utils/pipex_extend_1.c \
	    bonus/src/utils/back_fnct/fnc_gen1.c bonus/src/utils/back_fnct/fnc_gen2.c \
	    bonus/src/utils/back_fnct/ft_split.c \
	    bonus/src/utils/manage_error/error1.c bonus/src/utils/manage_error/error2.c \
	    include/gnl/get_next_line.c include/gnl/get_next_line_utils.c

OBJ = $(SRCS:%.c=build/%.o)
OBJSB = $(SRCSB:%.c=build/%.o)

all: $(NAME)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(PRINTF_LIB)

bonus: $(NAMEB)

$(NAMEB): $(OBJSB) $(PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(NAMEB) $(OBJSB) $(PRINTF_LIB)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	rm -rf build
	$(MAKE) clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME) $(NAMEB)
	$(MAKE) fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
