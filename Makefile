# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 03:31:28 by cacharle          #+#    #+#              #
#    Updated: 2020/02/09 22:38:47 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
MAKE_ARGS = -no-print-child

PHILO_ONE_DIR = philo_one
PHILO_TWO_DIR = philo_two
PHILO_THREE_DIR = philo_three

help:
	@echo "make common - build common lib"
	@echo "make philo_one - compile philo_one"
	@echo "make philo two - compile philo_one"
	@echo "make philo three - compile philo_one"

common:
	$(MAKE) $(MAKE_ARGS) $(COMMON_DIR)

philo_one: common
	$(MAKE) $(MAKE_ARGS) $(PHILO_ONE_DIR)

philo_two: common
	$(MAKE) $(MAKE_ARGS) $(PHILO_TWO_DIR)

philo_two: common
	$(MAKE) $(MAKE_ARGS) $(PHILO_THREE_DIR)