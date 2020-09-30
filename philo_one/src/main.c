/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:53:02 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 08:06:03 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_philo_conf	conf;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_routine_arg	*routine_args;

	if (!parse_args((t_philo_args*)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0)
		return (0);
	if ((forks = forks_new(conf.philo_num)) == NULL)
		return (1);
	if ((philos = philos_new(conf.philo_num)) == NULL)
		return (1);
	if ((routine_args = forks_dispatch(philos, forks, &conf)) == NULL)
		return (1);
	conf.all_alive = true;
	pthread_mutex_init(&conf.mutex_all_alive, NULL);
	pthread_mutex_init(&conf.mutex_stdout, NULL);
	if (!philos_start(philos, routine_args, conf.philo_num))
		return (1);
	while (conf.all_alive)
		;
	philos_detach(philos, conf.philo_num);
	pthread_mutex_destroy(&conf.mutex_stdout);
	pthread_mutex_destroy(&conf.mutex_all_alive);
	free(routine_args);
	free(philos);
	forks_destroy(forks, conf.philo_num);
	return (0);
}
