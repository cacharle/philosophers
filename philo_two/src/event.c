/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 10:24:44 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		event_take_fork(t_philo *arg)
{
	sem_wait(arg->conf->sem_forks);
	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_FORK, arg->conf->initial_time);
	sem_post(arg->conf->sem_stdout);
}

void		event_eat(t_philo *arg)
{
	sem_wait(arg->sem_eat);
	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_EAT, arg->conf->initial_time);
	sem_post(arg->conf->sem_stdout);
	arg->time_last_eat = h_time_now();
	sem_post(arg->sem_eat);
	h_sleep(arg->conf->timeout_eat);
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
	sem_post(arg->conf->sem_forks);
	sem_post(arg->conf->sem_forks);
	h_sleep(arg->conf->timeout_sleep);
}

void		event_die(t_philo *arg)
{
	sem_wait(arg->conf->sem_stdout);
	philo_put(arg->id, EVENT_DIE, arg->conf->initial_time);
	sem_post(arg->conf->sem_finish);
}
