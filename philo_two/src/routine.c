/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:00:07 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 10:30:04 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*routine_philo(t_philo *arg)
{
	long int	eat_counter;
	pthread_t	thread_death;

	eat_counter = 0;
	sem_wait(arg->conf->sem_start);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (t_routine)routine_death, arg) != 0)
		return (NULL);
	while (true)
	{
		sem_wait(arg->conf->sem_grab);
		event_take_fork(arg);
		event_take_fork(arg);
		sem_post(arg->conf->sem_grab);
		event_eat(arg);
		if (arg->conf->meal_num != -1 && ++eat_counter == arg->conf->meal_num)
		{
			sem_wait(arg->conf->sem_stdout);
			sem_post(arg->conf->sem_meal_num);
			sem_post(arg->conf->sem_stdout);
		}
		event_sleep(arg);
		event_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(t_philo *arg)
{
	while (true)
	{
		sem_wait(arg->sem_eat);
		if (h_time_now() - arg->time_last_eat > arg->conf->timeout_death)
			break ;
		sem_post(arg->sem_eat);
		usleep(2000);
	}
	event_die(arg);
	return (NULL);
}

#define PHILO_SEM_EAT_PREFIX "semaphore_philo_two_eat_"

t_philo	*routine_create_philos(t_philo_conf *conf)
{
	long int	i;
	t_philo		*philos;
	const char	*name;

	if ((philos = malloc(sizeof(t_philo) * conf->philo_num)) == NULL)
		return (NULL);
	i = -1;
	while (++i < conf->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].conf = conf;
		name = philo_sem_eat_name(PHILO_SEM_EAT_PREFIX, philos[i].id);
		sem_unlink(name);
		philos[i].sem_eat = sem_open(name, O_CREAT | O_EXCL, 0700, 1);
		if (philos[i].sem_eat == SEM_FAILED)
		{
			free(philos);
			return (NULL);
		}
	}
	return (philos);
}
