/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 09:43:16 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*routine_philo(t_philo *arg)
{
	pthread_t		thread_death;

	if (!arg->conf->all_alive)
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (t_routine)routine_death, arg) != 0)
		return (NULL);
	io_think(arg);
	while (arg->conf->all_alive)
	{
		io_take_fork(arg, arg->fork_left);
		io_take_fork(arg, arg->fork_right);
		arg->time_last_eat = h_time_now();
		io_eat(arg);
		io_sleep(arg, arg->fork_right, arg->fork_left);
		io_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(t_philo *arg)
{
	t_time			current;

	current = h_time_now();
	while (arg->conf->all_alive &&
			current - arg->time_last_eat < arg->conf->timeout_death)
		current = h_time_now();
	if (!arg->conf->all_alive)
		return (NULL);
	io_die(arg);
	return (NULL);
}
