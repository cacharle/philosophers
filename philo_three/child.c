/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 01:40:05 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/15 01:46:20 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	child_start(t_philo_args *philo_args)
{
	pthread_t		thread_death;

	io_think(arg);
	if (!arg->args->all_alive)
		return (NULL);
	arg->time_last_eat = h_time_now();
	if (pthread_create(&thread_death, NULL, routine_death, arg) != 0)
		return (NULL);
	
	while (arg->running)
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
