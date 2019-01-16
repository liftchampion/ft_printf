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

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIB)
	clang -o $(NAME) $(OBJS) $(LIB) $(FLAGS)

$(LIB):
	make -C libft/ all

$(OBJS): $(SRCS) $(HEADERS)
	clang $(FLAGS) -c $(SRCS)



link_d: build_d $(LIB)
	clang -o $(NAME) $(OBJS) $(LIB) -g

build_d: $(SRCS) $(HEADERS)
	clang -c -g $(SRCS)

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

re_lib:
	make -C libft/ re

re_this: fclean_this all

re: fclean all

valgrind: fclean_this link_d
	/Users/ggerardy/.brew/bin/valgrind --leak-check=full --show-leak-kinds=definite ./$(NAME)
