# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 19:25:02 by juwkim            #+#    #+#              #
#    Updated: 2023/02/11 07:11:47 by juwkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#	Define the compiler and flags											   #
# ---------------------------------------------------------------------------- #

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror -march=native -O2 -pipe -fsanitize=address
CPPFLAGS			= -I includes -I $(libft)/includes -I $(data-structures)/includes
DEPFLAGS			= -MMD -MP -MF $(BUILD_DIR)/$(DEP_DIR)/$*.d
LDFLAGS				= -L $(libft) -L $(data-structures) -L/Users/juwkim/.brew/opt/readline/lib
LDLIBS				:= -l ft -l datastructure -l ft -l readline

ifeq ($(shell uname -s), Linux)
	CFLAGS += -Wno-unused-result -fsanitize=leak
endif

# ---------------------------------------------------------------------------- #
#	Define the libraries													   #
# ---------------------------------------------------------------------------- #

libft				:= libft
data-structures		:= data-structures

# ---------------------------------------------------------------------------- #
#	Define the directories													   #
# ---------------------------------------------------------------------------- #

SRC_DIR				:=	sources

TOKENIZER_DIR		:=	tokenizer
LEXER_DIR			:=	lexer
PARSER_DIR			:=	parser
EXPANDER_DIR		:=	expander
EXECUTOR_DIR		:=	executor
BUILTIN_DIR			:=	builtin
UTILS_DIR			:=	utils

BUILD_DIR			:=	build
OBJ_DIR				:=	obj
DEP_DIR				:=	dep

# ---------------------------------------------------------------------------- #
#	Define the source files													   #
# ---------------------------------------------------------------------------- #

SRCS				:= $(addprefix $(SRC_DIR)/, main.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(TOKENIZER_DIR)/, tokenizer.c utils.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(LEXER_DIR)/, lexer.c utils.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(PARSER_DIR)/, parser.c redirection.c command.c commands_tree.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(EXPANDER_DIR)/, expander.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(EXECUTOR_DIR)/, executor.c cmd.c group.c pipeline.c exit_status.c not_builtin.c redirection.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(BUILTIN_DIR)/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
SRCS				+= $(addprefix $(SRC_DIR)/$(UTILS_DIR)/, environment.c is_valid_variable_name.c print.c signal_handler.c)

OBJS				:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/$(OBJ_DIR)/%.o, $(SRCS))
DEPS				:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/$(DEP_DIR)/%.d, $(SRCS))

# ---------------------------------------------------------------------------- #
#	Define the variables for progress bar									   #
# ---------------------------------------------------------------------------- #

TOTAL_FILES			:=	$(shell echo $(SRCS) | wc -w)
COMPILED_FILES		:=	0
STEP				:=	100

# ---------------------------------------------------------------------------- #
#	Define the target														   #
# ---------------------------------------------------------------------------- #

NAME				:=	minishell

# ---------------------------------------------------------------------------- #
#	Define the rules														   #
# ---------------------------------------------------------------------------- #

all: $(libft) $(data-structures)
	@$(MAKE) -C $(libft)
	@$(MAKE) -C $(data-structures)
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	@printf "\n$(MAGENTA)[$(NAME)] Linking Success\n$(DEF_COLOR)"
	
$(BUILD_DIR)/$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | dir_guard
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@
	@$(eval COMPILED_FILES = $(shell expr $(COMPILED_FILES) + 1))
	@$(eval PROGRESS = $(shell expr $(COMPILED_FILES) "*" $(STEP) / $(TOTAL_FILES)))
	@printf "                                                                                                   \r"
	@printf "$(YELLOW)[$(NAME)] [%02d/%02d] ( %3d %%) Compiling $<\r$(DEF_COLOR)" $(COMPILED_FILES) $(TOTAL_FILES) $(PROGRESS)

clean:
	@$(MAKE) -C $(libft) clean
	@$(MAKE) -C $(data-structures) clean
	@$(RM) -r $(BUILD_DIR)
	@printf "$(BLUE)[$(NAME)] obj. dep. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"

fclean:
	@$(MAKE) -C $(libft) fclean
	@$(MAKE) -C $(data-structures) fclean
	@$(RM) -r $(BUILD_DIR) $(NAME)
	@printf "$(BLUE)[$(NAME)] obj. dep. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"
	@printf "$(CYAN)[$(NAME)] exec. files$(DEF_COLOR)$(GREEN)	=> Cleaned!\n$(DEF_COLOR)"

re: fclean
	@$(MAKE) -C $(libft)
	@$(MAKE) -C $(data-structures)
	@$(MAKE) all
	@printf "$(GREEN)[$(NAME)] Cleaned and rebuilt everything!\n$(DEF_COLOR)"

dir_guard:
	@mkdir -p $(addprefix $(BUILD_DIR)/$(OBJ_DIR)/, $(TOKENIZER_DIR) \
	$(LEXER_DIR) $(PARSER_DIR) $(EXPANDER_DIR) $(EXECUTOR_DIR) \
	$(BUILTIN_DIR) $(UTILS_DIR))
	@mkdir -p $(addprefix $(BUILD_DIR)/$(DEP_DIR)/, $(TOKENIZER_DIR) \
	$(LEXER_DIR) $(PARSER_DIR) $(EXPANDER_DIR) $(EXECUTOR_DIR) \
	$(BUILTIN_DIR) $(UTILS_DIR))

norm:
	@(norminette | grep Error) || (printf "$(GREEN)[$(NAME)] Norminette Success\n$(DEF_COLOR)")

test:
	@cd tests && bash tester.sh a

.PHONY: all clean fclean re dir_guard norm test

# ---------------------------------------------------------------------------- #
#	Define the colors														   #
# ---------------------------------------------------------------------------- #

DEF_COLOR	=	\033[1;39m
GRAY		=	\033[1;90m
RED			=	\033[1;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[1;94m
MAGENTA		=	\033[1;95m
CYAN		=	\033[1;96m
WHITE		=	\033[1;97m

-include $(DEPS)
