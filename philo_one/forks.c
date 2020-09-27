/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:46:40 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/27 09:26:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t	*forks_new(int num)
{
	int				i;
	pthread_mutex_t	*forks;

	if ((forks = malloc(num * sizeof(pthread_mutex_t))) == NULL)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			forks_destroy(forks, i + 1);
			return (NULL);
		}
	}
	return (forks);
}

void			forks_destroy(pthread_mutex_t *forks, int num)
{
	while (num-- > 0)
		pthread_mutex_destroy(&forks[num]);
	free(forks);
}

t_routine_arg	*forks_dispatch(
	t_philo *philos,
	pthread_mutex_t *forks,
	t_philo_conf *conf)
{
	int				i;
	t_routine_arg	*routine_args;

	if ((routine_args = malloc(conf->philo_num * sizeof(t_routine_arg))) == NULL)
		return (NULL);
	i = -1;
	while (++i < conf->philo_num)
	{
		routine_args[i].conf = conf;
		routine_args[i].philo = philos + i;
		routine_args[i].fork_left = forks + i % conf->philo_num;
		routine_args[i].fork_right = forks + (i + 1) % conf->philo_num;
	}
	return (routine_args);
}