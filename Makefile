# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glambrig <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 13:10:05 by glambrig          #+#    #+#              #
#    Updated: 2024/02/13 16:38:08 by glambrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Source files
SRC = src/exec/builtins.c \
		src/exec/builtins_echo.c \
		src/exec/builtins_export.c \
		src/exec/copy_envp_into_list.c \
		src/exec/signals.c \
		src/exec/pipes.c \
		src/exec/utils.c \
		src/utils/linked_list_functions.c \
		src/utils/utils_parsing.c \
		src/parsing/bools_parsing_1.c \
		src/parsing/bools_parsing_2.c \
		src/parsing/bools_parsing_3.c \
		src/parsing/main_parser.c \
		src/parsing/new_nodes.c \
		src/parsing/pars_struct_fts.c \
		src/parsing/path_splitting.c \
		src/parsing/print_final_struct.c \
		src/parsing/split_2.c \
		src/parsing/split_parser.c \
		src/parsing/turbo_parser_2.c \
		src/parsing/turbo_parser.c \
		src/minishell.c

# Object files
OBJ = $(SRC:.c=.o)

# Link libft and other libs
LDFLAGS = -L./lft -lft -lreadline

#Specify libft's object files
LFT = ./lft/*.o

# Executable
NAME = minishell

all: $(NAME)

# Link object files into executable
$(NAME): $(LFT) $(OBJ)
	$(CC) $(SRC) -o $@ $(LDFLAGS) $(CFLAGS)

# Compile libft
$(LFT):
	$(MAKE) -C ./lft
#$(MAKE) bonus -C ./lft

# Clean up object files and executable
clean:
	rm -rf $(OBJ)
	$(MAKE) -C ./lft clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C ./lft fclean

re: fclean all
