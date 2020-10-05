/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:00:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/05 16:03:38 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*routine_philo(t_philo *arg)
{
	pthread_t	thread_death;

	event_think(arg);
	if (!arg->conf->all_alive)
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (t_routine)routine_death, arg) != 0)
		return (NULL);
	while (arg->conf->all_alive)
	{
		event_take_fork(arg);
		event_take_fork(arg);
		event_eat(arg);
		arg->time_last_eat = h_time_now();
		event_sleep(arg);
		event_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(t_philo *arg)
{
	t_time	current;

	current = h_time_now();
	while (arg->conf->all_alive
			&& current - arg->time_last_eat < arg->conf->timeout_death)
		current = h_time_now();
	event_die(arg);
	return (NULL);
}

t_philo	*routine_create_philos(t_philo_conf *conf, sem_t *forks)
{
	int		i;
	t_philo	*philos;

	if ((philos = malloc(sizeof(t_philo) * conf->philo_num)) == NULL)
		return (NULL);
	i = -1;
	while (++i < conf->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].forks = forks;
		philos[i].conf = conf;
	}
	return (philos);
}
