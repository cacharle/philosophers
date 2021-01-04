/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:36:16 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/04 11:03:58 by cacharle         ###   ########.fr       */
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
		usleep(500);
	}
	event_die(philo);
	return (NULL);
}

void	st_child_loop(t_philo *philo)
{
	long int	eat_counter;

	eat_counter = 0;
	while (true)
	{
		event_take_fork(philo);
		philo->time_last_eat = h_time_now();
		event_eat(philo);
		eat_counter++;
		if (philo->conf->meal_num != -1 && eat_counter == philo->conf->meal_num)
		{
			sem_wait(philo->sem_stdout);
			sem_post(philo->sem_finish);
			sem_post(philo->sem_stdout);
		}
		event_sleep(philo);
		event_think(philo);
	}
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
		philo->sem_finish = sem_open(PHILO_SEM_FINISH_NAME, 0);
		philo->sem_start = sem_open(PHILO_SEM_START_NAME, 0);
		philo->time_last_eat = h_time_now();
		pthread_create(&thread_death, NULL, (t_routine)routine_death, philo);
		event_think(philo);
		sem_wait(philo->sem_start);
		if (philo->id % 2 == 0)
			usleep(500);
		st_child_loop(philo);
		exit(0);
	}
	return (pid);
}
