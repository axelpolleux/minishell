# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ethutin- <ethutin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/17 10:24:21 by apolleux          #+#    #+#              #
#    Updated: 2026/03/20 15:00:52 by ethutin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -Iincludes -Iincludes/lib -MMD -MP
LDFLAGS		:=   
LDLIBS		:= -lreadline

SRC_DIR		:= src
BUILD_DIR	:= build

SRCS		:= $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS		:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS		:= $(OBJS:.o=.d)

# ------------------------------- UI (neon) ----------------------------------
NO_COLOR	:= \033[0m
BOLD		:= \033[1m
DIM		:= \033[2m

CYAN		:= \033[38;5;51m
PINK		:= \033[38;5;207m
LIME		:= \033[38;5;118m
PURPLE		:= \033[38;5;141m

BAR_WIDTH	:= 30
PROGRESS	:= 0
TOTAL		:= $(words $(OBJS))

define render_progress
$(eval PROGRESS := $(shell expr $(PROGRESS) + 1))
@$(SHELL) -c 'p=$$((100*$(PROGRESS)/$(TOTAL))); \
filled=$$((p*$(BAR_WIDTH)/100)); \
empty=$$(( $(BAR_WIDTH) - filled )); \
bar=""; i=0; while [ $$i -lt $$filled ]; do bar="$$bar#"; i=$$((i+1)); done; \
i=0; while [ $$i -lt $$empty ]; do bar="$$bar-"; i=$$((i+1)); done; \
m=$$(( $(PROGRESS) % 4 )); \
case $$m in 0) s="|";; 1) s="/";; 2) s="-";; 3) s="\\";; esac; \
printf "\r$(PINK)⚡$(NO_COLOR) $(CYAN)[%s]$(NO_COLOR) $(LIME)%3d%%%s$(NO_COLOR) $(DIM)%s$(NO_COLOR)" "$$bar" "$$p" "$$s" " $<";'
endef

all: $(NAME)

ifeq ($(strip $(OBJS)),)
$(NAME):
	@printf "$(PINK)✗$(NO_COLOR) no sources found in $(SRC_DIR) (add .c files to build)\n"
	@false
else
$(NAME): $(OBJS)
	@printf "\n$(PURPLE)↯$(NO_COLOR) $(BOLD)link$(NO_COLOR) $(NAME)\n"
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@printf "$(LIME)✓$(NO_COLOR) $(BOLD)built$(NO_COLOR) $(NAME)\n"
endif

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call render_progress)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(PINK)⌁$(NO_COLOR) $(BOLD)clean$(NO_COLOR) objects\n"
	rm -rf $(BUILD_DIR)

fclean: clean
	@printf "$(PINK)⌁$(NO_COLOR) $(BOLD)clean$(NO_COLOR) binary\n"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
