# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/24 05:50:15 by cacharle          #+#    #+#              #
#    Updated: 2021/01/14 10:56:18 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f
MKDIR = mkdir -p
MAKE = make --no-print-directory

COMMONDIR = ../common

CC = gcc
CCFLAGS = -std=c99 -O2 -I$(COMMONDIR)/inc -Wall -Wextra -Werror
LDFLAGS = -lpthread -L$(COMMONDIR) -lphilocommon

NAME = philo_two

SRCDIR = src
OBJDIR = obj

SRC = $(shell find $(SRCDIR) -type f -name '*.c')
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	$(MKDIR) $(OBJDIR)

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
