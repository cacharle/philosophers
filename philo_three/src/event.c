/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 14:47:49 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		event_take_fork(t_philo *arg)
{
	sem_wait(arg->forks);
	sem_wait(&arg->conf->mutex_stdout);
	philo_put(arg->id, EVENT_FORK);
	sem_post(&arg->conf->mutex_stdout);
}

void		event_eat(t_philo *arg)
{
	int	eat_counter;

	eat_counter = 0;
	while (eat_counter < arg->conf->meal_num)
	{
		sem_wait(&arg->conf->mutex_stdout);
		philo_put(arg->id, EVENT_EAT);
		sem_post(&arg->conf->mutex_stdout);
		usleep(arg->conf->timeout_eat * 1000);
		eat_counter++;
	}
}

void		event_think(t_philo *arg)
{
	sem_wait(&arg->conf->mutex_stdout);
	philo_put(arg->id, EVENT_THINK);
	sem_post(&arg->conf->mutex_stdout);
}

void		event_sleep(int id, t_time timeout_sleep, sem_t *sem_stdout, sem_t )
{
	sem_wait(sem_stdout);
	philo_put(id, EVENT_SLEEP);
	sem_post(sem_stdout);
	sem_post(arg->forks);
	sem_post(arg->forks);
	usleep(arg->conf->timeout_sleep * 1000);
}

void		event_die(int id, sem_t *sem_stdout, sem_t *sem_dead)
{
	sem_wait(sem_stdout);
	philo_put(arg->id, EVENT_DIE);
	arg->conf->all_alive = false;
	sem_post(sem_dead);
}
