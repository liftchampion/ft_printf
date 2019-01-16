# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 15:05:00 by ehugh-be          #+#    #+#              #
#    Updated: 2018/12/30 04:15:43 by ehugh-be         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = $(wildcard *.c) 
OBJ=$(SRC:.c=.o)
CC = clang
#CFLAGS = -Wall -Wextra -Werror
LIB = libft/libft.a
LIBDIR = libft/
LIBSPATH = -I libft/ -I /usr/local/include/
HDR = fdf.h
LINK = -lmlx -framework OpenGL -framework AppKit -L /usr/local/lib/

all: lib $(OBJ) $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(LIBSPATH) -o $(NAME) $(LINK) $(LIB) $(OBJ)

lib:  
	make -C $(LIBDIR)

%.o: %.c $(HDR) $(LIB)
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK)

fclean: clean
	/bin/rm -f $(NAME) 
	make -C $(LIBDIR) fclean

clean: cleanlib
	/bin/rm -f $(OBJ)

cleanlib: 
	make -C $(LIBDIR) clean

re: fclean all

