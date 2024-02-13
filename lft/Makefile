# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glambrig <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 15:24:36 by glambrig          #+#    #+#              #
#    Updated: 2023/05/08 11:50:37 by glambrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a

#CC and CFLAGS variables are mandatory names if you want automatic compilation

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_memset.c \
      ft_bzero.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_strlen.c \
      ft_isalpha.c \
      ft_isdigit.c \
      ft_isalnum.c \
      ft_isascii.c \
      ft_isprint.c \
      ft_toupper.c \
      ft_tolower.c \
      ft_strchr.c \
      ft_strrchr.c \
      ft_strncmp.c \
      ft_strlcpy.c \
      ft_strlcat.c \
      ft_strnstr.c \
      ft_atoi.c \
      ft_calloc.c \
      ft_strdup.c \
      ft_substr.c \
      ft_strjoin.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      ./ft_printf/ft_printf.c \
      ./ft_printf/ft_printf_utils.c \
      ./ft_printf/ft_printf_2utils.c \
	  #./gnl/get_next_line.c

BONUSSRC = ft_lstnew.c \
	   ft_lstadd_front.c \
	   ft_lstsize.c \
	   ft_lstlast.c \
	   ft_lstadd_back.c \
	   ft_lstdelone.c \
	   ft_lstclear.c \
	   ft_lstiter.c \
	   ft_lstmap.c \

BONUSOBJ = $(BONUSSRC:.c=.o)

OBJ = $(SRC:.c=.o)

all: $(NAME)

bonus: $(BONUSOBJ)
	ar rcs $(NAME) $^

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

clean:
	rm -f *.o
	rm -f ./*/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
