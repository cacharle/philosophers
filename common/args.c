/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:12:55 by cacharle          #+#    #+#             */
/*   Updated: 2020/12/30 13:44:54 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	parse_args(t_philo_args *args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		return (h_err(false, "Usage: %s philosophers_num death_timeout"
			"eat_timeout sleep_timeout [meal_num]", argv[0]));
	}
	if ((args->philo_num = h_atou_strict(argv[1])) == -1
		|| (args->timeout_death = h_atou_strict(argv[2])) == -1
		|| (args->timeout_eat = h_atou_strict(argv[3])) == -1
		|| (args->timeout_sleep = h_atou_strict(argv[4])) == -1)
		return (false);
	if (argc == 6)
	{
		if ((args->meal_num = h_atou_strict(argv[5])) == -1)
			return (false);
	}
	else
		args->meal_num = -1;
	return (true);
}
