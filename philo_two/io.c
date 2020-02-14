/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 23:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 23:50:10 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			io_eat(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_eat(arg->id, arg->args->timeout_eat);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}

void			io_think(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_think(arg->id);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}

void			io_sleep(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_sleep(arg->id, arg->args->timeout_sleep);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}

void			io_die(t_routine_arg *arg)
{
	pthread_mutex_lock(&arg->args->mutex_stdout);
	if (arg->args->all_alive)
		philo_die(arg->id);
	pthread_mutex_unlock(&arg->args->mutex_stdout);
}
