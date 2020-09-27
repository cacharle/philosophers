# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 05:50:15 by cacharle          #+#    #+#              #
#    Updated: 2020/09/27 10:35:32 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f

CC = gcc
CCFLAGS = -Wall -Wextra #-Werror
LDFLAGS = -lpthread

NAME = philo_one

SRC = main.c \
	  philo.c \
	  forks.c \
	  routine.c \
	  io.c \
	  common.c \
	  helper.c

OBJDIR = obj

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	@mkdir -pv $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all prebuild clean fclean re
