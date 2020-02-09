/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:47:14 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/10 01:29:25 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo				*philos_new(int num)
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
		philos[i].id = i + 1;
		philos[i].alive = FALSE;
	}
	return (philos);
}

void				philos_destroy(t_philo *philos, int num)
{
	(void)num;
	if (philos == NULL)
		return ;
	free(philos);
}

t_bool	philos_start(t_philo *philos, t_routine_arg *routine_args, int num)
{
	t_routine_arg	*routine_arg;
	int				i;

	i = -1;
	while (++i < num)
	{
		philos[i].alive = TRUE;
		if (pthread_create(philos[i].thread, NULL, philo_one_routine, (void*)(routine_args + i)) == -1)
			return (FALSE);
	}
	return (TRUE);
}

void	philos_join(t_philo *philos, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (philos[i].alive)
		{
			philos[i].alive = FALSE;
			pthread_join(philos[i].thread, NULL);
		}
	}
}

t_bool	philos_starved(t_philo *philos, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		if (!philos[i].alive)
		{
			i = -1;
			while (++i < num)
				philos[i].alive = FALSE;
			return (TRUE);
		}
	return (FALSE);
}
