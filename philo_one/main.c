/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:53:02 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 01:41:21 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


int	main(int argc, char **argv)
{
	t_philo_args	philo_args;
	t_philo			*philos;
	t_fork			*forks;
	t_routine_arg	*routine_args;
	/* mutex_t			mutex_stdout; */

	/* pthread_mutex_init(mutex_stdout); */
	if (!parse_args(&philo_args, argc, argv))
		return (1);
	if ((forks = forks_new(philo_args.philo_num)) == NULL)
		return (1);
	if ((philos = philos_new(philo_args.philo_num)) == NULL)
	{
		free(forks);
		return (1);
	}
	if ((routine_args = forks_dispatch(philos, forks, &philo_args)) == NULL)
	{
		free(philos);
		free(forks);
		return (1);
	}
	if (!philos_start(philos, routine_args, philo_args.philo_num))
	{
		free(philos);
		free(forks);
		free(routine_args);
		return (1);
	}
	while (TRUE)
		if (philos_starved(philos, philo_args.philo_num))
			break;
	philos_join(philos, philo_args.philo_num);
	free(routine_args);
	free(philos);
	forks_destroy(forks, philo_args.philo_num);
	return (0);
}
