/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:00:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/15 00:35:26 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*routine_philo(void *void_arg)
{
	t_routine_arg	*arg;
	pthread_t		thread_death;

	arg = (t_routine_arg*)void_arg;
	io_think(arg);
	if (!arg->args->all_alive)
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, routine_death, arg) != 0)
		return (NULL);
	while (arg->args->all_alive)
	{
		sem_wait(arg->forks);
		sem_wait(arg->forks);
		io_eat(arg);
		sem_post(arg->forks);
		sem_post(arg->forks);
		arg->time_last_eat = h_time_now();
		io_sleep(arg);
		io_think(arg);
	}
	pthread_join(thread_death, NULL);
	return (NULL);
}

void	*routine_death(void *void_arg)
{
	t_routine_arg	*arg;
	t_time			current;

	arg = (t_routine_arg*)void_arg;
	current = h_time_now();
	while (arg->args->all_alive &&
			current - arg->time_last_eat < arg->args->timeout_death)
		current = h_time_now();
	io_die(arg);
	pthread_mutex_lock(&arg->args->mutex_all_alive);
	arg->args->all_alive = FALSE;
	pthread_mutex_unlock(&arg->args->mutex_all_alive);
	return (NULL);
}

t_routine_arg	*routine_args_create(t_philo_args *philo_args, sem_t *forks)
{
	int				i;
	t_routine_arg	*routine_args;

	if ((routine_args = malloc(sizeof(t_routine_arg) * philo_args->philo_num)) == NULL)
		return (NULL);
	i = -1;
	while (++i < philo_args->philo_num)
	{
		routine_args[i].id = i + 1;
		routine_args[i].forks = forks;
		routine_args[i].args = philo_args;
	}
	return (routine_args);
}
