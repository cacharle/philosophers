/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 21:37:50 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/27 10:33:29 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	philo_put(int id, t_philo_event event)
{
	h_putnbr(h_time_now());
	h_putchar(' ');
	h_putnbr(id);
	if (event == EVENT_FORK)
		h_putstr(" has taken fork\n");
	else if (event == EVENT_EAT)
		h_putstr(" is eating\n");
	else if (event == EVENT_SLEEP)
		h_putstr(" is sleeping\n");
	else if (event == EVENT_THINK)
		h_putstr(" is thinking\n");
	else if (event == EVENT_DIE)
		h_putstr(" died\n");
}

void		io_eat(t_routine_arg *arg)
{
	int	eat_counter;

	eat_counter = 0;
	while (eat_counter < arg->conf->meal_num)
	{
		if (!arg->conf->all_alive)
			return ;
		pthread_mutex_lock(&arg->conf->mutex_stdout);
		philo_put(arg->philo->id, EVENT_EAT);
		pthread_mutex_unlock(&arg->conf->mutex_stdout);
		usleep(arg->conf->timeout_eat * 1000);
		eat_counter++;
	}
}

void		io_think(t_routine_arg *arg)
{
	if (!arg->conf->all_alive)
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->philo->id, EVENT_THINK);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}

void		io_sleep(t_routine_arg *arg)
{
	if (!arg->conf->all_alive)
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->philo->id, EVENT_SLEEP);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
	usleep(arg->conf->timeout_sleep * 1000);
}

void		io_die(t_routine_arg *arg)
{
	if (!arg->conf->all_alive)
		return ;
	pthread_mutex_lock(&arg->conf->mutex_stdout);
	philo_put(arg->philo->id, EVENT_DIE);
	pthread_mutex_unlock(&arg->conf->mutex_stdout);
}
