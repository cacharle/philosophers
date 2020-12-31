/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:36:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/12/31 19:12:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*routine_death(t_philo *philo)
{
	t_time	current;

	current = h_time_now();
	while (current - philo->time_last_eat < philo->conf->timeout_death)
	{
		current = h_time_now();
		usleep(200);
	}
	event_die(philo);
	return (NULL);
}

pid_t	child_start(t_philo *philo)
{
	pthread_t	thread_death;
	pid_t		pid;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		philo->forks = sem_open(PHILO_SEM_NAME, 0);
		philo->sem_stdout = sem_open(PHILO_SEM_STDOUT_NAME, 0);
		philo->sem_dead = sem_open(PHILO_SEM_DEAD_NAME, 0);
		philo->time_last_eat = h_time_now();
		pthread_create(&thread_death, NULL, (t_routine)routine_death, philo);
		event_think(philo);
		while (true)
		{
			event_take_fork(philo);
			event_take_fork(philo);
			philo->time_last_eat = h_time_now();
			event_eat(philo);
			event_sleep(philo);
			event_think(philo);
		}
		exit(0);
	}
	return (pid);
}
