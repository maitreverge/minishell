# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flverge <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 13:10:05 by glambrig          #+#    #+#              #
#    Updated: 2024/01/31 10:07:19 by flverge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Source files
SRC = builtins.c \
		builtins_echo.c \
		builtins_export.c \
		copy_envp_into_list.c \

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

# Clean up object files and executable
clean:
	rm -rf $(OBJ)
	$(MAKE) -C ./lft clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C ./lft fclean

re: fclean all
