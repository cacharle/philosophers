# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 03:31:28 by cacharle          #+#    #+#              #
#    Updated: 2020/02/09 03:32:56 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
MAKE_ARGS = -no-print-child

PHILO_ONE_DIR = philo_one
PHILO_TWO_DIR = philo_two
PHILO_THREE_DIR = philo_three

philo_one:
	$(MAKE) $(MAKE_ARGS) $(PHILO_ONE_DIR)

philo_two:
	$(MAKE) $(MAKE_ARGS) $(PHILO_TWO_DIR)

philo_two:
	$(MAKE) $(MAKE_ARGS) $(PHILO_THREE_DIR)
