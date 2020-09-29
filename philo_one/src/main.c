/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:53:02 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/29 13:26:07 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_philo_conf	philo_args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_routine_arg	*routine_args;

	if (!parse_args(&philo_args, argc, argv))
		return (1);
	if (philo_args.philo_num == 0)
		return (0);
	if ((forks = forks_new(philo_args.philo_num)) == NULL)
		return (1);
	if ((philos = philos_new(philo_args.philo_num)) == NULL)
		return (1);
	if ((routine_args = forks_dispatch(philos, forks, &philo_args)) == NULL)
		return (1);
	philo_args.all_alive = true;
	pthread_mutex_init(&philo_args.mutex_all_alive, NULL);
	pthread_mutex_init(&philo_args.mutex_stdout, NULL);
	if (!philos_start(philos, routine_args, philo_args.philo_num))
		return (1);
	/* pthread_mutex_lock(philo_args.mutex_all_alive); */
	/* pthread_mutex_lock(philo_args.mutex_all_alive); */
	while (philo_args.all_alive)
		;
	philos_join(philos, philo_args.philo_num);
	pthread_mutex_destroy(&philo_args.mutex_stdout);
	pthread_mutex_destroy(&philo_args.mutex_all_alive);
	free(routine_args);
	free(philos);
	forks_destroy(forks, philo_args.philo_num);
	return (0);
}
