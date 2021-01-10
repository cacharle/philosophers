/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:36:16 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 10:39:19 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*routine_death(t_philo *philo)
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

void	st_child_loop(t_philo *philo)
{
	long int	eat_counter;

	eat_counter = 0;
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

pid_t	child_start(t_philo *philo)
{
	pthread_t	thread_death;
	pid_t		pid;
	const char	*sem_eat_name;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		philo->forks = sem_open(PHILO_SEM_NAME, 0);
		philo->sem_stdout = sem_open(PHILO_SEM_STDOUT_NAME, 0);
		philo->sem_finish = sem_open(PHILO_SEM_FINISH_NAME, 0);
		philo->sem_meal_num = sem_open(PHILO_SEM_MEAL_NUM_NAME, 0);
		philo->sem_start = sem_open(PHILO_SEM_START_NAME, 0);
		philo->sem_grab = sem_open(PHILO_SEM_GRAB_NAME, 0);
		sem_eat_name = philo_sem_eat_name(PHILO_SEM_EAT_PREFIX, philo->id);
		sem_unlink(sem_eat_name);
		philo->sem_eat = sem_open(sem_eat_name, O_CREAT | O_EXCL, 0700, 1);
		sem_wait(philo->sem_start);
		philo->time_last_eat = h_time_now();
		pthread_create(&thread_death, NULL, (t_routine)routine_death, philo);
		pthread_detach(thread_death);
		st_child_loop(philo);
		exit(0);
	}
	return (pid);
}
