# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 22:39:08 by cacharle          #+#    #+#              #
#    Updated: 2021/01/08 14:32:37 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar rcs
RM = rm -f
MKDIR = mkdir -pv

SRCDIR = src
OBJDIR = obj
INCDIR = inc

CC = gcc
CCFLAGS = -std=c99 -Wall -Wextra -Werror -O2 -I$(INCDIR)

NAME = libphilocommon.a

SRC = $(shell find $(SRCDIR) -type f -name "*.c")
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	@$(MKDIR) $(OBJDIR)

$(NAME): $(OBJ)
	$(LIB) $(NAME) $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: clean all

.PHONY: all prebuild clean re
