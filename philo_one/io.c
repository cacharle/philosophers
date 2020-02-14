/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 21:42:30 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			io_eat(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_eat(arg->philo->id, arg->args->timeout_eat);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}

void			io_think(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_think(arg->philo->id);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}

void			io_sleep(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_sleep(arg->philo->id, arg->args->timeout_sleep);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}

void			io_die(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_die(arg->philo->id);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}
