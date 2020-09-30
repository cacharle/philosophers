/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 09:56:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		event_take_fork(t_philo *arg)
{
	sem_wait(arg->forks);
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_FORK);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}

void		event_eat(t_philo *arg)
{
	int	eat_counter;

	eat_counter = 0;
	while (eat_counter < arg->conf->meal_num)
	{
		pthread_mutex_lock(&arg->conf->mutex_stdout);
		if (!arg->conf->all_alive)
			return ;
		philo_put(arg->id, EVENT_EAT);
		pthread_mutex_unlock(&arg->conf->mutex_stdout);
		usleep(arg->conf->timeout_eat * 1000);
		eat_counter++;
	}
}

void		event_think(t_philo *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_THINK);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}

void		event_sleep(t_philo *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_SLEEP);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	sem_post(arg->forks);
	sem_post(arg->forks);
	usleep(arg->conf->timeout_sleep * 1000);
}

void		event_die(t_philo *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_DIE);
	arg->conf->all_alive = false;
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}
