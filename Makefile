#Basics
CC				:= cc
CFLAGS			:= -Wall -Werror -Wextra -g -fsanitize=address -MMD -MP

INCLUDES_DIR	:= -Iincludes/ -Iincludes/libft/ -Iincludes/lib/ -Iincludes/gnl
INCLUDES		:= $(INCLUDES_DIR)
LIBS			:= -lreadline
NAME			:= minishell

LIBFT_DIR		:= includes/libft/
LIBFT			:= $(LIBFT_DIR)libft.a

GNL_DIR			:= includes/gnl/
GNL_SRCS		:= $(GNL_DIR)get_next_line.c	\
				$(GNL_DIR)get_next_line_utils.c

#Files
BUILDS_DIR		:= builds
SRCS := $(shell find src -type f -name "*.c") \
        $(GNL_SRCS)
OBJS			:= $(patsubst %.c, $(BUILDS_DIR)/%.o, $(SRCS))
DEPS			:= $(OBJS:.o=.d)

#Rules

all: $(NAME)

-include $(DEPS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "Minishell [READY]"

$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "Libft [READY]"

FORCE:

$(BUILDS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# 	@echo "Compiling: $<"

clean:
	@echo "[CLEAN]"
	@rm -rf $(BUILDS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@echo "[FCLEAN]"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re FORCE