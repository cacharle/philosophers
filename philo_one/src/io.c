/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 09:43:31 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		io_take_fork(t_philo *arg, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_FORK);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}

void		io_eat(t_philo *arg)
{
	int	eat_counter;

	eat_counter = 0;
	while (eat_counter < arg->conf->meal_num)
	{
		pthread_mutex_lock(&arg->conf->mutex_stdout);
		if (!arg->conf->all_alive)
			return ;
		philo_put(arg->id, EVENT_EAT);
		pthread_mutex_unlock(&arg->conf->mutex_stdout);
		usleep(arg->conf->timeout_eat * 1000);
		eat_counter++;
	}
}

void		io_think(t_philo *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_THINK);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}

void		io_sleep(t_philo *arg, pthread_mutex_t *fork_right, pthread_mutex_t *fork_left)
{
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	philo_put(arg->id, EVENT_SLEEP);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	pthread_mutex_unlock(fork_right);
	pthread_mutex_unlock(fork_left);
	usleep(arg->conf->timeout_sleep * 1000);
}

void		io_die(t_philo *arg)
{
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (!arg->conf->all_alive)
		return ;
	arg->conf->all_alive = false;
	philo_put(arg->id, EVENT_DIE);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}
