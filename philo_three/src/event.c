/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/01 09:04:39 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		event_take_fork(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_FORK);
	sem_post(philo->sem_stdout);
}

void		event_eat(t_philo *philo)
{
	int	eat_counter;

	eat_counter = 0;
	while (eat_counter < philo->conf->meal_num)
	{
		sem_wait(philo->sem_stdout);
		philo_put(philo->id, EVENT_EAT);
		sem_post(philo->sem_stdout);
		usleep(philo->conf->timeout_eat * 1000);
		eat_counter++;
	}
}

void		event_think(t_philo *philo)
{
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_THINK);
	sem_post(philo->sem_stdout);
}

void		event_sleep(t_philo *philo)
{
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_SLEEP);
	sem_post(philo->sem_stdout);
	sem_post(philo->forks);
	sem_post(philo->forks);
	usleep(philo->conf->timeout_sleep * 1000);
}

void		event_die(t_philo *philo)
{
	sem_wait(philo->sem_stdout);
	philo_put(philo->id, EVENT_DIE);
	sem_post(philo->sem_dead);
}
