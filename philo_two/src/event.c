/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/24 13:02:01 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		event_take_fork(t_philo *arg)
{
	sem_wait(arg->forks);
	sem_wait(arg->conf->sem_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_FORK);
	sem_post(arg->conf->sem_stdout);
}

void		event_eat(t_philo *arg)
{
	int	eat_counter;

	eat_counter = 0;
	while (eat_counter < arg->conf->meal_num)
	{
		sem_wait(arg->conf->sem_stdout);
		if (!arg->conf->all_alive)
			return ;
		philo_put(arg->id, EVENT_EAT);
		sem_post(arg->conf->sem_stdout);
		usleep(arg->conf->timeout_eat * 1000);
		eat_counter++;
	}
}

void		event_think(t_philo *arg)
{
	sem_wait(arg->conf->sem_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_THINK);
	sem_post(arg->conf->sem_stdout);
}

void		event_sleep(t_philo *arg)
{
	sem_wait(arg->conf->sem_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_SLEEP);
	sem_post(arg->conf->sem_stdout);
	sem_post(arg->forks);
	sem_post(arg->forks);
	usleep(arg->conf->timeout_sleep * 1000);
}

void		event_die(t_philo *arg)
{
	sem_wait(arg->conf->sem_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_DIE);
	arg->conf->all_alive = false;
	sem_post(arg->conf->sem_stdout);
}
