# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 22:33:54 by ggerardy          #+#    #+#              #
#    Updated: 2018/12/13 01:58:26 by ggerardy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = printf
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
LIB = ./libft/libft.a
HEADERS = $(wildcard *.h)
FLAGS = -Wall -Wextra -Werror
DFLAGS = -g
CC = clang

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIB)
	clang -o $(NAME) $(OBJS) $(LIB) $(FLAGS)

%.o: %.c $(HDR) $(LIB)
	$(CC) $(FLAGS) -c $< -o $@

$(LIB):
	make -C libft/ all

debug: FLAGS = $(DFLAGS)
debug: fclean_this all


clean_lib:
	make -C libft/ clean

clean_this:
	rm -f $(OBJS)

clean: clean_lib clean_this

fclean_lib:
	make -C libft/ fclean

fclean_this: clean_this
	rm -f $(NAME)

fclean: fclean_lib fclean_this

re_this: fclean_this all

re: fclean all

valgrind: debug
	~/.brew/bin/valgrind --leak-check=full --show-leak-kinds=definite ./$(NAME)
