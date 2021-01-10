/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:00:07 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 13:39:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	*st_routine_death(t_philo *arg)
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

static void	st_check_meal_num_finished(t_philo *arg, long int eat_counter)
{
	if (arg->conf->meal_num != -1 && eat_counter == arg->conf->meal_num)
	{
		sem_wait(arg->conf->sem_stdout);
		sem_post(arg->conf->sem_meal_num);
		sem_post(arg->conf->sem_stdout);
	}
}

void		*routine_philo(t_philo *arg)
{
	long int	eat_counter;
	pthread_t	thread_death;

	eat_counter = 0;
	sem_wait(arg->conf->sem_start);
	arg->time_last_eat = h_time_now();
	if (pthread_create(
		&thread_death, NULL, (t_routine)st_routine_death, arg) != 0)
		return (NULL);
	pthread_detach(thread_death);
	arg->time_last_eat = h_time_now();
	while (true)
	{
		sem_wait(arg->conf->sem_grab);
		event_take_fork(arg);
		event_take_fork(arg);
		sem_post(arg->conf->sem_grab);
		event_eat(arg);
		eat_counter++;
		st_check_meal_num_finished(arg, eat_counter);
		event_sleep(arg);
		event_think(arg);
	}
	return (NULL);
}

t_philo		*routine_create_philos(t_philo_conf *conf)
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
			while (i-- > 0)
				sem_unlink(philo_sem_eat_name(
					PHILO_SEM_EAT_PREFIX, philos[i].id));
			free(philos);
			return (NULL);
		}
	}
	return (philos);
}
