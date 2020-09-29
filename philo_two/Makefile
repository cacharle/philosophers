# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 05:50:15 by cacharle          #+#    #+#              #
#    Updated: 2020/09/29 15:21:43 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f

# COMMON_DIR = ../common

CC = gcc
CCFLAGS = -Wall -Wextra #-I$(COMMON_DIR) -Werror
LDFLAGS = -lpthread #-L$(COMMON_DIR) -lphilocommon

NAME = philo_two

SRCDIR = src
OBJDIR = obj

SRC = $(shell find $(SRCDIR) -type f -name '*.c')
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# common_all:
# 	make -C $(COMMON_DIR) all
#
# common_fclean:
# 	make -C $(COMMON_DIR) fclean
