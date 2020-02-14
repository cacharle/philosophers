/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 00:45:23 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*routine_philo(void *void_arg)
{
	t_routine_arg	*arg;
	pthread_t		thread_death;

	arg = (t_routine_arg*)void_arg;
	if (pthread_create(&thread_death, NULL, routine_death, arg) != 0)
		return (NULL);
	philo_think(arg->philo->id);
	while (arg->philo->alive)
	{
		if (!arg->fork_left->used && !arg->fork_right->used)
		{
			pthread_mutex_lock(&arg->fork_left->mutex);
			pthread_mutex_lock(&arg->fork_right->mutex);
			philo_eat(arg->philo->id, arg->args->timeout_eat);
			pthread_mutex_unlock(&arg->fork_left->mutex);
			pthread_mutex_unlock(&arg->fork_right->mutex);
			philo_sleep(arg->philo->id, arg->args->timeout_sleep);
			philo_think(arg->philo->id);
		}
	}
	if (arg->philo->alive)
		philo_die(arg->philo->id);
	/* pthread_join( */
	free(arg);
	return (NULL);
}

void	*routine_death(void *void_arg)
{
	t_routine_arg	*arg;
	t_time			current;
	struct timeval	tv;

	arg = (t_routine_arg*)void_arg;
	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	current = h_timeval_to_time(&tv);
	while (arg->philo->alive &&
			current - arg->philo->time_last_eat < arg->args->timeout_death)
	{
		if (gettimeofday(&tv, NULL) == -1)
			return (NULL);
		current = h_timeval_to_time(&tv);
	}
	arg->philo->alive = FALSE;
	return (NULL);
}
