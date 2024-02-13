# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flverge <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 13:10:05 by glambrig          #+#    #+#              #
#    Updated: 2024/02/13 21:05:37 by flverge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME = minishell

# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Source files
SRC = $(wildcard src/exec/*.c) \
    $(wildcard src/utils/*.c) \
    $(wildcard src/parsing/*.c) \
    src/minishell.c

# Object files
OBJ = $(SRC:.c=.o)

# Link libft and other libs
LDFLAGS = -L./lft -lft -lreadline

#Specify libft's object files
LFT = ./lft/*.o

# MakeFile Colors
RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[33m

all: $(NAME)

# Link object files into executable
$(NAME): $(LFT) $(OBJ)
	@echo "$(BOLD)$(RED)🛠️            Compiling minishell          🛠️$(RESET)"
	@$(CC) $(SRC) -o $@ $(LDFLAGS) $(CFLAGS)
	@echo "$(BOLD)$(GREEN)🥳      minishell fully compiled, ready to use      🥳$(RESET)"

# Compile libft
$(LFT):
	@echo "$(BOLD)$(RED)🛠️            Compiling libft          🛠️$(RESET)"
	@make -s -C ./lft
	@echo "$(BOLD)$(GREEN)😎            Libft Compiled          😎$(RESET)"
#$(MAKE) bonus -C ./lft

# Clean up object files and executable
clean:
	@rm -rf $(OBJ)
	@make clean -s -C ./lft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C ./lft

re: fclean all

.PHONY: all clean fclean re