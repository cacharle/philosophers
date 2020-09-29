/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:47:14 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/29 13:29:49 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo	*philos_new(int num)
{
	int		i;
	t_philo	*philos;

	if (num < 0)
		return (NULL);
	if ((philos = malloc(num * sizeof(t_philo))) == NULL)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		philos[i].id = i + 1;
		philos[i].alive = false;
	}
	return (philos);
}

bool	philos_start(t_philo *philos, t_routine_arg *routine_args, int num)
{
	int				i;

	i = -1;
	while (++i < num)
	{
		philos[i].alive = true;
		if (pthread_create(&philos[i].thread, NULL,
							(void *(*)(void*))routine_philo, (void*)(routine_args + i)) == -1)
			return (false);
	}
	return (true);
}

void	philos_join(t_philo *philos, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (philos[i].alive)
		{
			philos[i].alive = false;
			pthread_detach(philos[i].thread);
		}
	}
}
