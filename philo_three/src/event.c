/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/08 20:25:44 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		event_take_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_FORK, philo->initial_time);
	philo_put_flush();
	sem_post(philo->sem_stdout);
}

void		event_eat(t_philo *philo)
{
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_EAT, philo->initial_time);
	philo_put_flush();
	sem_post(philo->sem_stdout);
	h_sleep(philo->conf->timeout_eat);
}

void		event_think(t_philo *philo)
{
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_THINK, philo->initial_time);
	philo_put_flush();
	sem_post(philo->sem_stdout);
}

void		event_sleep(t_philo *philo)
{
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_SLEEP, philo->initial_time);
	philo_put_flush();
	sem_post(philo->sem_stdout);
	sem_post(philo->forks);
	sem_post(philo->forks);
	h_sleep(philo->conf->timeout_sleep);
}

void		event_die(t_philo *philo)
{
	long int i;

	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_DIE, philo->initial_time);
	philo_put_flush();
	if (philo->conf->meal_num == -1)
		sem_post(philo->sem_finish);
	else
	{
		i = -1;
		while (++i < philo->conf->philo_num)
			sem_post(philo->sem_finish);
	}
}
