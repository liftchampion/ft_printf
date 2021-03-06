# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 22:33:54 by ggerardy          #+#    #+#              #
#    Updated: 2019/02/19 11:07:06 by ggerardy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OBJS2 = $(wildcard libft/*.o)
LIB = ./libft/libft.a
LIBSPATH = -I ./libft
HEADERS = $(wildcard *.h)
FLAGS = -Wall -Wextra -Werror
DFLAGS = -g
CC = clang

.PHONY: all clean fclean re

all: lib $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@ar r $(NAME) $(OBJS) $(OBJS2)
	#$(CC) $(LIBSPATH) -o ft_printf $(OBJS) $(LIB) $(FLAGS)

%.o: %.c $(HDR) $(LIB)
	$(CC) $(FLAGS) $(LIBSPATH) -c $< -o $@

libftprintf.a: $(LIB) $(NAME)

$(LIB): lib

lib:
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
