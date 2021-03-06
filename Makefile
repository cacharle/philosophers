# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 03:31:28 by cacharle          #+#    #+#              #
#    Updated: 2020/12/30 13:48:29 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make --no-print-directory

PHILO_ONE_DIR   = philo_one
PHILO_TWO_DIR   = philo_two
PHILO_THREE_DIR = philo_three

help:
	@echo "make philo_one   - compile philo_one"
	@echo "make philo_two   - compile philo_two"
	@echo "make philo_three - compile philo_three"

philo_one:
	$(MAKE) -C $(PHILO_ONE_DIR)

philo_two:
	$(MAKE) -C $(PHILO_TWO_DIR)

philo_three:
	$(MAKE) -C $(PHILO_THREE_DIR)

.PHONY: philo_one philo_two philo_three help
