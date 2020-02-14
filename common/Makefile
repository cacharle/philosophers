# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 22:39:08 by cacharle          #+#    #+#              #
#    Updated: 2020/02/14 00:49:18 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar rcs
RM = rm -rf

CC = gcc
CCFLAGS = -Wall -Wextra #-Werror

NAME = libphilocommon.a

SRC = $(shell find . -type f -name "*.c")
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(LIB) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
