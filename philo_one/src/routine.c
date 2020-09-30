/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 08:17:21 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*routine_philo(t_routine_arg *arg)
{
	pthread_t		thread_death;

	if (!arg->conf->all_alive)
		return (NULL);
	arg->philo->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (void *(*)(void*))routine_death, arg) != 0)
		return (NULL);
	io_think(arg);
	while (arg->conf->all_alive)
	{
		io_take_fork(arg, arg->fork_left);
		io_take_fork(arg, arg->fork_right);
		arg->philo->time_last_eat = h_time_now();
		io_eat(arg);
		io_sleep(arg, arg->fork_right, arg->fork_left);
		io_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(t_routine_arg *arg)
{
	t_time			current;

	current = h_time_now();
	while (arg->conf->all_alive &&
			current - arg->philo->time_last_eat < arg->conf->timeout_death)
		current = h_time_now();
	if (!arg->conf->all_alive)
		return (NULL);
	pthread_mutex_lock(&arg->conf->mutex_all_alive);
	io_die(arg);
	arg->conf->all_alive = false;
	pthread_mutex_unlock(&arg->conf->mutex_all_alive);
	return (NULL);
}
