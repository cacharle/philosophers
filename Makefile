# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 03:31:28 by cacharle          #+#    #+#              #
#    Updated: 2020/02/14 22:44:40 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
MAKE_ARGS = --no-print-directory

COMMON_DIR = common
PHILO_ONE_DIR = philo_one
PHILO_TWO_DIR = philo_two
PHILO_THREE_DIR = philo_three

help:
	@echo "make common       - build common lib"
	@echo "make philo_one    - compile philo_one"
	@echo "make philo_two    - compile philo_one"
	@echo "make philo_three  - compile philo_one"

.PHONY: common
common:
	$(MAKE) $(MAKE_ARGS) -C $(COMMON_DIR)

.PHONY: philo_one
philo_one:
	$(MAKE) $(MAKE_ARGS) -C $(PHILO_ONE_DIR)

.PHONY: philo_two
philo_two:
	$(MAKE) $(MAKE_ARGS) -C $(PHILO_TWO_DIR)

.PHONY: philo_three
philo_three:
	$(MAKE) $(MAKE_ARGS) -C $(PHILO_THREE_DIR)
