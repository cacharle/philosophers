# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 05:50:15 by cacharle          #+#    #+#              #
#    Updated: 2020/02/14 23:37:39 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f

COMMON_DIR = ../common

CC = gcc
CCFLAGS = -I$(COMMON_DIR) -Wall -Wextra #-Werror
LDFLAGS = -lpthread -L$(COMMON_DIR) -lphilocommon

NAME = philo_two

SRC = main.c \
	  io.c \
	  routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): common_all $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: common_fclean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

common_all:
	make -C $(COMMON_DIR) all

common_fclean:
	make -C $(COMMON_DIR) fclean
