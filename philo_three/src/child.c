/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:36:16 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 14:24:05 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*st_routine_death(t_philo *philo)
{
	while (true)
	{
		sem_wait(philo->sem_eat);
		if (h_time_now() - philo->time_last_eat > philo->conf->timeout_death)
			break ;
		sem_post(philo->sem_eat);
		usleep(2000);
	}
	event_die(philo);
	return (NULL);
}

static void	st_child_loop(t_philo *philo)
{
	long int	eat_counter;

	eat_counter = 0;
	philo->time_last_eat = h_time_now();
	while (true)
	{
		sem_wait(philo->sem_grab);
		event_take_fork(philo);
		event_take_fork(philo);
		sem_post(philo->sem_grab);
		event_eat(philo);
		eat_counter++;
		if (philo->conf->meal_num != -1 && eat_counter == philo->conf->meal_num)
		{
			sem_wait(philo->sem_stdout);
			sem_post(philo->sem_meal_num);
			sem_post(philo->sem_stdout);
		}
		event_sleep(philo);
		event_think(philo);
	}
}

#define PHILO_SEM_EAT_PREFIX "semaphore_philo_three_eat_"

static bool	st_child_setup(t_philo *philo)
{
	if (!h_sem_create(PHILO_SEM_FINISH_NAME, 0, &philo->sem_finish) ||
		!h_sem_create(philo_sem_eat_name(PHILO_SEM_EAT_PREFIX, philo->id),
			1, &philo->sem_eat) ||
		!h_sem_create(PHILO_SEM_NAME, 0, &philo->forks) ||
		!h_sem_create(PHILO_SEM_STDOUT_NAME, 0, &philo->sem_stdout) ||
		!h_sem_create(PHILO_SEM_MEAL_NUM_NAME, 0, &philo->sem_meal_num) ||
		!h_sem_create(PHILO_SEM_START_NAME, 0, &philo->sem_start) ||
		!h_sem_create(PHILO_SEM_GRAB_NAME, 0, &philo->sem_grab))
		return (false);
	return (true);
}

pid_t		child_start(t_philo *philo)
{
	pthread_t	thread_death;
	pid_t		pid;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		philo->sem_finish = SEM_FAILED;
		if (!st_child_setup(philo))
		{
			if (philo->sem_finish != SEM_FAILED)
				sem_post(philo->sem_finish);
			exit(1);
		}
		sem_wait(philo->sem_start);
		philo->time_last_eat = h_time_now();
		if (pthread_create(&thread_death, NULL,
				(t_routine)st_routine_death, philo) != 0)
			exit(sem_post(philo->sem_finish));
		pthread_detach(thread_death);
		st_child_loop(philo);
		exit(0);
	}
	return (pid);
}
