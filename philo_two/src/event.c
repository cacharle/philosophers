/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/03 13:55:28 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		event_take_fork(t_philo *arg)
{
	sem_wait(arg->forks);
	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_FORK, arg->conf->initial_time);
	sem_post(arg->conf->sem_stdout);
}

void		event_eat(t_philo *arg)
{
	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_EAT, arg->conf->initial_time);
	sem_post(arg->conf->sem_stdout);
	usleep(arg->conf->timeout_eat * 1000);
}

void		event_think(t_philo *arg)
{
	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_THINK, arg->conf->initial_time);
	sem_post(arg->conf->sem_stdout);
}

void		event_sleep(t_philo *arg)
{
	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_SLEEP, arg->conf->initial_time);
	sem_post(arg->conf->sem_stdout);
	sem_post(arg->forks);
	sem_post(arg->forks);
	usleep(arg->conf->timeout_sleep * 1000);
}

void		event_die(t_philo *arg)
{
	long int	i;

	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_DIE, arg->conf->initial_time);
	if (arg->conf->meal_num == -1)
		sem_post(arg->conf->sem_finish);
	else
	{
		i = -1;
		while (++i < arg->conf->philo_num)
			sem_post(arg->conf->sem_finish);
	}
}
