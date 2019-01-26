# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 22:33:54 by ggerardy          #+#    #+#              #
#    Updated: 2019/01/18 14:25:13 by ehugh-be         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = printf
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
LIB = ./libft/libft.a
LIBSPATH = -I ./libft
HEADERS = $(wildcard *.h)
FLAGS = -Wall -Wextra -Werror
DFLAGS = -g
CC = clang

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIB)
	$(CC) $(LIBSPATH) -o $(NAME) $(OBJS) $(LIB) $(FLAGS)

%.o: %.c $(HDR) $(LIB)
	$(CC) $(FLAGS) $(LIBSPATH) -c $< -o $@

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
	~/.brew/bin/valgrind --leak-check=full --show-leak-kinds=definite --dsymutil=yes --track-origins=yes ./$(NAME)
