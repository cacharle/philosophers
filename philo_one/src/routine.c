/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/04 10:42:48 by cacharle         ###   ########.fr       */
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

void		*routine_philo(t_philo *arg)
{
	pthread_t	thread_death;
	long int	eat_counter;

	pthread_mutex_lock(&arg->mutex_start);
	if (philo_finished(arg->conf))
		return (NULL);
	if (arg->id % 2 == 0)
		usleep(1000);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (t_routine)routine_death, arg) != 0)
		return (NULL);
	eat_counter = 0;
	while (!philo_finished(arg->conf))
	{
		event_take_fork(arg);
		arg->time_last_eat = h_time_now();
		event_eat(arg);
		eat_counter++;
		st_check_meal_num_finished(arg, eat_counter);
		event_sleep(arg, arg->fork_right, arg->fork_left);
		event_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void		*routine_death(t_philo *arg)
{
	while (!philo_finished(arg->conf) &&
			h_time_now() - arg->time_last_eat < arg->conf->timeout_death)
		usleep(500);
	event_die(arg);
	return (NULL);
}
