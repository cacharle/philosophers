# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 05:50:15 by cacharle          #+#    #+#              #
#    Updated: 2021/01/01 14:45:16 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f
MAKE = make --no-print-directory

COMMONDIR = ../common

CC = gcc
CCFLAGS = -g -I$(COMMONDIR) -std=c99 -Wall -Wextra -Werror
LDFLAGS = -lpthread -L$(COMMONDIR) -lphilocommon

NAME = philo_two

SRCDIR = src
OBJDIR = obj

SRC = $(shell find $(SRCDIR) -type f -name '*.c')
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	@mkdir -p $(OBJDIR)

$(NAME): common_all $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: common_clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

common_all:
	$(MAKE) -C $(COMMONDIR) all

common_clean:
	$(MAKE) -C $(COMMONDIR) clean

.PHONY: all prebuild clean fclean re common_all common_clean
