/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 12:05:19 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

inline bool	philo_finished(t_philo_conf *conf)
{
	return (!conf->all_alive ||
			(conf->meal_num != -1 &&
				conf->meal_num_finished_counter == conf->philo_num));
}

static void	st_check_meal_num_finished(t_philo *arg, long int eat_counter)
{
	if (!philo_finished(arg->conf) && arg->conf->meal_num != -1 &&
		eat_counter == arg->conf->meal_num)
	{
		pthread_mutex_lock(&arg->conf->mutex_meal_num_finished_counter);
		arg->conf->meal_num_finished_counter++;
		pthread_mutex_unlock(&arg->conf->mutex_meal_num_finished_counter);
	}
}

static void	st_take_both_forks(t_philo *arg)
{
	if (arg->id % 2 == 0)
	{
		event_take_fork(arg, arg->fork_left);
		event_take_fork(arg, arg->fork_right);
	}
	else
	{
		event_take_fork(arg, arg->fork_right);
		event_take_fork(arg, arg->fork_left);
	}
}

static void	*st_routine_death(t_philo *arg)
{
	while (!philo_finished(arg->conf))
	{
		pthread_mutex_lock(&arg->mutex_eat);
		if (h_time_now() - arg->time_last_eat > arg->conf->timeout_death)
			break ;
		pthread_mutex_unlock(&arg->mutex_eat);
		usleep(2000);
	}
	event_die(arg);
	return (NULL);
}

void		*routine_philo(t_philo *arg)
{
	pthread_t	thread_death;
	long int	eat_counter;

	eat_counter = 0;
	pthread_mutex_lock(&arg->mutex_start);
	if (philo_finished(arg->conf))
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL,
				(t_routine)st_routine_death, arg) != 0)
		return (NULL);
	pthread_detach(thread_death);
	arg->time_last_eat = h_time_now();
	while (!philo_finished(arg->conf))
	{
		st_take_both_forks(arg);
		event_eat(arg);
		eat_counter++;
		st_check_meal_num_finished(arg, eat_counter);
		event_sleep(arg, arg->fork_right, arg->fork_left);
		event_think(arg);
	}
	return (NULL);
}
