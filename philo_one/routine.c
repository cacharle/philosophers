/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 21:22:52 by cacharle         ###   ########.fr       */
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
	if (!arg->args->all_alive)
		return (NULL);
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_think(arg->philo->id);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
	while (arg->args->all_alive)
	{
		if (!arg->fork_left->used && !arg->fork_right->used)
		{
			pthread_mutex_lock(&arg->fork_left->mutex);
			pthread_mutex_lock(&arg->fork_right->mutex);
			arg->fork_left->used = TRUE;
			arg->fork_right->used = TRUE;
			pthread_mutex_unlock(&arg->fork_left->mutex);
			pthread_mutex_unlock(&arg->fork_right->mutex);

			arg->philo->time_last_eat = h_time_now();
			pthread_mutex_lock(&arg->args->mutex_stdout);
			if (arg->args->all_alive)
				philo_eat(arg->philo->id, arg->args->timeout_eat);
			pthread_mutex_unlock(&arg->args->mutex_stdout);

			pthread_mutex_lock(&arg->fork_left->mutex);
			pthread_mutex_lock(&arg->fork_right->mutex);
			arg->fork_left->used = FALSE;
			arg->fork_right->used = FALSE;
			pthread_mutex_unlock(&arg->fork_left->mutex);
			pthread_mutex_unlock(&arg->fork_right->mutex);

			pthread_mutex_lock(&arg->args->mutex_stdout);
			if (arg->args->all_alive)
				philo_sleep(arg->philo->id, arg->args->timeout_sleep);
			pthread_mutex_unlock(&arg->args->mutex_stdout);

			pthread_mutex_lock(&arg->args->mutex_stdout);
			if (arg->args->all_alive)
				philo_think(arg->philo->id);
			pthread_mutex_unlock(&arg->args->mutex_stdout);
		}
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(void *void_arg)
{
	t_routine_arg	*arg;
	t_time			current;

	/* if (!arg->args->all_alive) */
	/* 	return (NULL); */
	arg = (t_routine_arg*)void_arg;

	current = h_time_now();
	/* pthread_mutex_lock(&arg->args->mutex_stdout); */
	/* 	printf("===\n"); */
	/* 	printf("%d crr %ld\n", arg->philo->id, current); */
	/* 	printf("%d lst %ld\n", arg->philo->id, arg->philo->time_last_eat); */
	/* 	printf("%d dif %ld\n", arg->philo->id, current - arg->philo->time_last_eat); */
	/* 	printf("===\n"); */
	/* pthread_mutex_unlock(&arg->args->mutex_stdout); */
	while (arg->args->all_alive &&
			current - arg->philo->time_last_eat < arg->args->timeout_death)
		current = h_time_now();
	pthread_mutex_lock(&arg->args->mutex_stdout);
	pthread_mutex_lock(&arg->args->mutex_all_alive);
	if (arg->args->all_alive)
		philo_die(arg->philo->id);
	arg->args->all_alive = FALSE;
	pthread_mutex_unlock(&arg->args->mutex_all_alive);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
	return (NULL);
}
