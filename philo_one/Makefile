# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 05:50:15 by cacharle          #+#    #+#              #
#    Updated: 2020/02/10 00:16:03 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f

COMMON_DIR = ../common

CC = gcc
CCFLAGS = -I$(COMMON_DIR) -Wall -Wextra #-Werror
LDFLAGS = -lpthread -L$(COMMON_DIR) -lphilocommon

NAME = philo_one

SRC = main.c \
	  philo.c \
	  fork.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
