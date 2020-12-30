/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 01:11:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/12/30 13:44:25 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*routine_philo(t_philo *arg)
{
	pthread_t		thread_death;
	long int		eat_counter;

	if (!arg->conf->all_alive)
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (t_routine)routine_death, arg) != 0)
		return (NULL);
	event_think(arg);
	eat_counter = 0;
	while (arg->conf->all_alive)
	{
		event_take_fork(arg, arg->fork_left);
		event_take_fork(arg, arg->fork_right);
		arg->time_last_eat = h_time_now();
		event_eat(arg);
		eat_counter++;
		if (arg->conf->meal_num != -1 && eat_counter == arg->conf->meal_num)
		{
			pthread_mutex_lock(&arg->conf->mutex_meal_num_finished_counter);
			arg->conf->meal_num_finished_counter++;
			pthread_mutex_unlock(&arg->conf->mutex_meal_num_finished_counter);
		}
		event_sleep(arg, arg->fork_right, arg->fork_left);
		event_think(arg);
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
	{
		current = h_time_now();
		usleep(200);
	}
	if (!arg->conf->all_alive)
		return (NULL);
	event_die(arg);
	return (NULL);
}
