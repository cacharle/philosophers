/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:00:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 08:41:23 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*routine_philo(t_routine_arg *arg)
{
	pthread_t		thread_death;

	io_think(arg);
	if (!arg->conf->all_alive)
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, (t_routine)routine_death, arg) != 0)
		return (NULL);
	while (arg->conf->all_alive)
	{
		io_take_fork(arg);
		io_take_fork(arg);
		io_eat(arg);
		arg->time_last_eat = h_time_now();
		io_sleep(arg);
		io_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(t_routine_arg *arg)
{
	t_time			current;

	current = h_time_now();
	while (arg->conf->all_alive &&
			current - arg->time_last_eat < arg->conf->timeout_death)
		current = h_time_now();
	pthread_mutex_lock(&arg->conf->mutex_all_alive);
	io_die(arg);
	arg->conf->all_alive = false;
	pthread_mutex_unlock(&arg->conf->mutex_all_alive);
	return (NULL);
}

t_routine_arg	*routine_args_create(t_philo_conf *conf, sem_t *forks)
{
	int				i;
	t_routine_arg	*routine_conf;

	if ((routine_conf = malloc(sizeof(t_routine_arg) * conf->philo_num)) == NULL)
		return (NULL);
	i = -1;
	while (++i < conf->philo_num)
	{
		routine_conf[i].id = i + 1;
		routine_conf[i].forks = forks;
		routine_conf[i].conf = conf;
	}
	return (routine_conf);
}
