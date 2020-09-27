/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:12:55 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/27 10:36:31 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

bool				parse_args(t_philo_conf *philo_args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (false);
	if ((philo_args->philo_num = h_atou_strict(argv[1])) == -1
		|| (philo_args->timeout_death = h_atou_strict(argv[2])) == -1
		|| (philo_args->timeout_eat = h_atou_strict(argv[3])) == -1
		|| (philo_args->timeout_sleep = h_atou_strict(argv[4])) == -1)
		return (false);
	if (argc == 6)
	{
		if ((philo_args->meal_num = h_atou_strict(argv[5])) == -1)
			return (false);
	}
	else
		philo_args->meal_num = 1;
	return (true);
}
