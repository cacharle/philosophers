/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:47:14 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/04 10:42:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo	*philos_new(t_philo_conf *conf, pthread_mutex_t *forks)
{
	long int	i;
	t_philo		*philos;

	if (conf->philo_num < 0)
		return (NULL);
	if ((philos = malloc(conf->philo_num * sizeof(t_philo))) == NULL)
		return (NULL);
	i = -1;
	while (++i < conf->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].conf = conf;
		philos[i].fork_left = forks + i % conf->philo_num;
		philos[i].fork_right = forks + (i + 1) % conf->philo_num;
		pthread_mutex_init(&philos[i].mutex_start, NULL);
		pthread_mutex_lock(&philos[i].mutex_start);
	}
	return (philos);
}

bool	philos_start(t_philo *philos, long int num)
{
	long int	i;

	i = -1;
	while (++i < num)
	{
		if (pthread_create(
				&philos[i].thread,
				NULL,
				(t_routine)routine_philo,
				(void*)(philos + i)) != 0)
		{
			while (--i >= 0)
				pthread_detach(philos[i].thread);
			return (false);
		}
	}
	i = -1;
	while (++i < num)
		pthread_mutex_unlock(&philos[i].mutex_start);
	return (true);
}

void	philos_detach(t_philo *philos, long int num)
{
	long int	i;

	if (philos == NULL)
		return ;
	i = -1;
	while (++i < num)
		pthread_detach(philos[i].thread);
}
