/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:46:40 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/10 00:34:17 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_fork	*forks_new(int num)
{
	int		i;
	t_fork	*forks;

	if ((forks = (t_fork*)malloc(sizeof(t_fork) * num)) == NULL)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&forks[num].mutex, NULL) != 0)
		{
			forks_destroy(forks, i + 1);
			return (NULL);
		}
	}
	return (forks);
}

void	forks_destroy(t_fork *forks, int num)
{
	while (num-- > 0)
	{
		forks[num].used = TRUE;
		pthread_mutex_destroy(&forks[num].mutex);
	}
}

t_routine_arg	*forks_dispatch(t_philo *philos, t_fork *forks, t_philo_args *args)
{
	int				i;
	t_routine_arg	*routine_args;

	if ((routine_args = (t_routine_arg*)malloc(sizeof(t_routine_arg) * args->philo_num)) == NULL)
		return (NULL);
	i = -1;
	while (++i < args->philo_num)
	{
		routine_args[i].args = args;
		routine_args[i].philo = philos + i;
		routine_args[i].fork_left = forks + i % args->philo_num;
		routine_args[i].fork_left = forks + (i - 1) % args->philo_num;
	}
	return (routine_args);
}
