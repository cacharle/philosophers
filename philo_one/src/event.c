/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/04 12:08:15 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	event_take_fork(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	pthread_mutex_lock(arg->fork_left);
	pthread_mutex_lock(arg->fork_right);
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_FORK, arg->conf->initial_time);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_FORK, arg->conf->initial_time);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}

void	event_eat(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_EAT, arg->conf->initial_time);
	if (arg->conf->philo_num < 30)
		philo_put_flush();
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	h_sleep(arg->conf->timeout_eat);
}

void	event_think(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_THINK, arg->conf->initial_time);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}

void	event_sleep(
	t_philo *arg,
	pthread_mutex_t *fork_right,
	pthread_mutex_t *fork_left)
{
	if (philo_finished(arg->conf))
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	if (philo_finished(arg->conf))
		return ;
	philo_put(arg->id, EVENT_SLEEP, arg->conf->initial_time);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	pthread_mutex_unlock(fork_right);
	pthread_mutex_unlock(fork_left);
	h_sleep(arg->conf->timeout_sleep);
}

void	event_die(t_philo *arg)
{
	if (philo_finished(arg->conf))
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->id, EVENT_DIE, arg->conf->initial_time);
	arg->conf->all_alive = false;
}
