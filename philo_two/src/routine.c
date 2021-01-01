/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:00:07 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/01 14:23:59 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

inline bool	philo_finished(t_philo_conf *conf)
{
	return (!conf->all_alive ||
			(conf->meal_num != -1 &&
				conf->meal_num_finished_counter == conf->philo_num));
}

void	*routine_philo(t_philo *arg)
{
	long int	eat_counter;
	pthread_t	thread_death;

	if (philo_finished(arg->conf))
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (t_routine)routine_death, arg) != 0)
		return (NULL);
	eat_counter = 0;
	event_think(arg);
	while (!philo_finished(arg->conf))
	{
		event_take_fork(arg);
		event_take_fork(arg);
		event_eat(arg);
		arg->time_last_eat = h_time_now();
		eat_counter++;
		if (!philo_finished(arg->conf) && arg->conf->meal_num != -1 &&
			eat_counter == arg->conf->meal_num)
		{
			sem_wait(arg->conf->sem_meal_num_finished_counter);
			arg->conf->meal_num_finished_counter++;
			sem_post(arg->conf->sem_meal_num_finished_counter);
		}
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
	while (!philo_finished(arg->conf)
			&& current - arg->time_last_eat < arg->conf->timeout_death)
	{
		current = h_time_now();
		usleep(200);
	}
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
