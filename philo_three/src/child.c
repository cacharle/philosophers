/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:36:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 14:39:58 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*routine_death(t_philo_args *arg)
{
	t_time	current;

	current = h_time_now();
	while (current - arg->time_last_eat < arg->conf->timeout_death)
		current = h_time_now();
	if (!arg->conf->all_alive)
		return (NULL);
	event_die(arg);
	return (NULL);
}

pid_t	child_start(t_philo_args *arg)
{
	pid_t	pid;
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_alive;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		forks = sem_open(PHILO_SEM_NAME, 0);
		sem_stdout = sem_open(PHILO_SEM_STDOUT_NAME, 0);
		pthread_create(&death_thread, NULL, (t_routine)routine_death, &args);
		event_think();
		while (true)
		{
			event_eat();
			event_sleep();
			event_think();
		}
		exit(0);
	}
	return pid;
}
