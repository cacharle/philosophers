/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 08:43:45 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		io_take_fork(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_all_alive);
	if (!arg->conf->all_alive)
		return ;
	sem_wait(arg->forks);
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->id, EVENT_FORK);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	pthread_mutex_unlock(&arg->conf->mutex_all_alive);
}

void		io_eat(t_routine_arg *arg)
{
	int	eat_counter;

	eat_counter = 0;
	while (eat_counter < arg->conf->meal_num)
	{
		pthread_mutex_lock(&arg->conf->mutex_all_alive);
		if (!arg->conf->all_alive)
			return ;
		pthread_mutex_lock(&arg->conf->mutex_stdout);
		philo_put(arg->id, EVENT_EAT);
		pthread_mutex_unlock(&arg->conf->mutex_stdout);
		pthread_mutex_unlock(&arg->conf->mutex_all_alive);
		usleep(arg->conf->timeout_eat * 1000);
		eat_counter++;
	}
}

void		io_think(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_all_alive);
	if (!arg->conf->all_alive)
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->id, EVENT_THINK);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	pthread_mutex_unlock(&arg->conf->mutex_all_alive);
}

void		io_sleep(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_all_alive);
	if (!arg->conf->all_alive)
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->id, EVENT_SLEEP);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	pthread_mutex_unlock(&arg->conf->mutex_all_alive);
	sem_post(arg->forks);
	sem_post(arg->forks);
	usleep(arg->conf->timeout_sleep * 1000);
}

void		io_die(t_routine_arg *arg)
{
	if (!arg->conf->all_alive)
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->id, EVENT_DIE);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}
