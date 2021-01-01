/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/01 15:57:43 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		event_take_fork(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	sem_wait(arg->forks);
	if (philo_finished(arg->conf))
		return ;
	sem_wait(arg->conf->sem_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_FORK);
	if (philo_finished(arg->conf))
		return ;
	sem_post(arg->conf->sem_stdout);
}

void		event_eat(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	sem_wait(arg->conf->sem_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_EAT);
	if (philo_finished(arg->conf))
		return ;
	sem_post(arg->conf->sem_stdout);
	usleep(arg->conf->timeout_eat * 1000);
}

void		event_think(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	sem_wait(arg->conf->sem_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_THINK);
	if (philo_finished(arg->conf))
		return ;
	sem_post(arg->conf->sem_stdout);
}

void		event_sleep(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	sem_wait(arg->conf->sem_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_SLEEP);
	if (philo_finished(arg->conf))
		return ;
	sem_post(arg->conf->sem_stdout);
	if (philo_finished(arg->conf))
		return ;
	sem_post(arg->forks);
	if (philo_finished(arg->conf))
		return ;
	sem_post(arg->forks);
	if (philo_finished(arg->conf))
		return ;
	usleep(arg->conf->timeout_sleep * 1000);
}

void		event_die(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	sem_wait(arg->conf->sem_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_DIE);
	arg->conf->all_alive = false;
	if (philo_finished(arg->conf))
		return ;
	sem_post(arg->conf->sem_stdout);
}
