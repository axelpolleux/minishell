CC            := cc
CFLAGS        := -Wall -Werror -Wextra -MMD -MP

INCLUDES_DIR  := -Iincludes/ -Iincludes/libft/ -Iincludes/lib/
INCLUDES      := $(INCLUDES_DIR)
LIBS          := -lreadline
NAME          := minishell

LIBFT_DIR     := includes/libft/
LIBFT         := $(LIBFT_DIR)libft.a

BUILDS_DIR    := builds

# Files
SRCS          := src/built_in/cd/cd.c \
                 src/built_in/cd/cd_expand.c \
                 src/built_in/echo/echo.c \
                 src/built_in/env/env.c \
                 src/built_in/exec_built.c \
                 src/built_in/exit/exit.c \
                 src/built_in/export/export.c \
                 src/built_in/export/export_extend1.c \
                 src/built_in/export/export_extend2.c \
                 src/built_in/pwd/pwd.c \
                 src/built_in/unset/unset.c \
                 src/built_in/utils/built_utils.c \
                 src/cmd/make_cmd_utils.c \
                 src/cmd/make_command.c \
                 src/env/make_env.c \
                 src/env/make_pwd.c \
                 src/executor/cmd_utils2.c \
                 src/executor/cmd_utils.c \
                 src/executor/executor2.c \
                 src/executor/executor.c \
                 src/executor/redir.c \
                 src/executor/wait_end.c \
                 src/expanding/central_expand.c \
                 src/expanding/expand_utils1.c \
                 src/expanding/expand_utils2.c \
                 src/heredoc/expand_here_doc.c \
                 src/heredoc/here_doc_manage.c \
                 src/heredoc/here_doc_utils.c \
                 src/lexer/parser.c \
                 src/lexer/tokeniser.c \
                 src/lexer/tokeniser_extand.c \
                 src/lexer/tokeniser_utils.c \
                 src/main.c \
                 src/signal_manage/signal.c \
                 src/utils/back_fnc/free.c \
                 src/utils/back_fnc/gen/fnc_gen1.c \
                 src/utils/back_fnc/gen/fnc_gen2.c \
                 src/utils/back_fnc/gen/fnc_gen3.c \
                 src/utils/back_fnc/gen/fnc_gen4.c \
                 src/utils/back_fnc/gen/fnc_gen5.c \
                 src/utils/back_fnc/init.c \
                 src/utils/error_management/error1.c \
                 src/utils/error_management/error2.c \
                 src/utils/error_management/error3.c \
                 src/utils/main_utils.c

OBJS          := $(patsubst %.c, $(BUILDS_DIR)/%.o, $(SRCS))
DEPS          := $(OBJS:.o=.d)

# Rules

all: $(NAME)

-include $(DEPS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "Minishell [READY]"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory -j
	@echo "Libft [READY]"

$(BUILDS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling: $<"

clean:
	@echo "[CLEAN]"
	@rm -rf $(BUILDS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@echo "[FCLEAN]"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re