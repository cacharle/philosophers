/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/10 01:19:13 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*routine_philo(t_routine_arg *routine_arg)
{
	pthread_t	thread_death;

	if (pthread_create(&thread_death, NULL, routine_death, routine_arg) != 0)
		return (NULL);
	philo_think(routine_arg->philo->id);
	while (routine_arg->philo->alive && !philo_starved(routine_arg->philo))
	{
		if (!routine_arg->fork_left->used && !routine_arg->fork_right->used)
		{
			pthread_mutex_lock(&routine_arg->fork_left->mutex);
			pthread_mutex_lock(&routine_arg->fork_right->mutex);
			philo_eat(routine_arg->philo->id, routine_arg->args->timeout_eat);
			pthread_mutex_unlock(&routine_arg->fork_left->mutex);
			pthread_mutex_unlock(&routine_arg->fork_right->mutex);
			philo_sleep(routine_arg->philo->id, routine_arg->args->timeout_sleep);
			philo_think(routine_arg->philo->id);
		}
	}
	if (routine_arg->philo->alive)
		philo_die(routine_arg->philo->id);
	free(routine_arg);
	return (NULL);
}

void			*routine_death(t_routine_arg *arg)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	while (arg->philo->alive &&
			arg->philo->time_last_eat - tv.asd > arg->args->timeout_death)
		if (gettimeofday(&tv, NULL) == -1)
			return (NULL);
	arg->philo->alive = FALSE;
	return (NULL);
}
