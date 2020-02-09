/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:54:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/09 03:26:07 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_philo				*philos_new(int num, t_philo_routine routine)
{
	int		i;
	t_philo	*philos;

	if (num < 0)
		return (NULL);
	if ((philos = (t_philo*)h_calloc(num + 1, sizeof(t_philo))) == NULL)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		philos[i].id = num + 1;
		if (pthread_create(&philos[i].thread, NULL, routine, philos + num) != 0)
		{
			philos_destroy(philos, i);
			return (NULL);
		}
	}
	return (philos);
}

void				philos_destroy(t_philo *philo, int num)
{
	if (philo == NULL)
		return ;
	while (num-- > 0)
		pthread_join(philos[num].thread, NULL);
	free(philos);
}

void				philo_eat(t_philo *philo)
{
	// take forks
	// lock mutex
	philo_put_state_change(philo, EVENT_EATING);
	usleep(philo->timeout_eat * 1000);
	// drop forks
	// unlock mutex
}

void				philo_sleep(t_philo *philo)
{
	philo_put_state_change(philo, EVENT_SLEEPING);
	usleep(philo->timeout_sleep * 1000);
}

void				philo_think(t_philo *philo)
{
	philo_put_state_change(philo, EVENT_THINKING);
	// search a fork
}
