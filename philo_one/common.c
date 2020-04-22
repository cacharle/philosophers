/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:12:55 by cacharle          #+#    #+#             */
/*   Updated: 2020/04/22 13:22:51 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

bool				parse_args(t_philo_conf *philo_args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (false);
	if ((philo_args->philo_num = h_atoi_strict_unsigned(argv[1])) == -1
		|| (philo_args->timeout_death = h_atoi_strict_unsigned(argv[2])) == -1
		|| (philo_args->timeout_eat = h_atoi_strict_unsigned(argv[3])) == -1
		|| (philo_args->timeout_sleep = h_atoi_strict_unsigned(argv[4])) == -1)
		return (false);
	if (argc == 6
		&& (philo_args->meal_num = h_atoi_strict_unsigned(argv[5])) == -1)
		return (false);
	else
		philo_args->meal_num = -1;
	return (true);
}
