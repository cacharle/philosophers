/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:54:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/09 23:56:26 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void				philo_eat(int id, int timeout)
{
	philo_put_state_change(id, EVENT_EATING);
	usleep(timeout * 1000);
}

void				philo_sleep(int id, int timeout)
{
	philo_put_state_change(id, EVENT_SLEEPING);
	usleep(timeout * 1000);
}

void				philo_think(int id)
{
	philo_put_state_change(id, EVENT_THINKING);
}

void				philo_die(int id)
{
	philo_put_state_change(id, EVENT_DIED);
}

