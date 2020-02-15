/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/15 01:25:41 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*routine_philo(void *void_arg)
{
	t_routine_arg	*arg;
	pthread_t		thread_death;

	arg = (t_routine_arg*)void_arg;
	if (!arg->args->all_alive)
		return (NULL);
	arg->philo->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, routine_death, arg) != 0)
		return (NULL);
	io_think(arg);
	while (arg->args->all_alive)
	{
		pthread_mutex_lock(arg->fork_left);
		pthread_mutex_lock(arg->fork_right);
		io_eat(arg);
		pthread_mutex_unlock(arg->fork_right);
		pthread_mutex_unlock(arg->fork_left);
		io_sleep(arg);
		io_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(void *void_arg)
{
	t_routine_arg	*arg;
	t_time			current;

	arg = (t_routine_arg*)void_arg;
	current = h_time_now();
	while (arg->args->all_alive &&
			current - arg->philo->time_last_eat < arg->args->timeout_death)
		current = h_time_now();
	io_die(arg);
	pthread_mutex_lock(&arg->args->mutex_all_alive);
	arg->args->all_alive = FALSE;
	pthread_mutex_unlock(&arg->args->mutex_all_alive);
	return (NULL);
}
