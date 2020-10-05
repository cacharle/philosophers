/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:53:02 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/05 15:42:09 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	st_setup(
	t_philo_conf *conf,
	t_philo **philos,
	pthread_mutex_t **forks)
{
	if ((*forks = forks_new(conf->philo_num)) == NULL)
		return (1);
	if ((*philos = philos_new(conf, *forks)) == NULL)
	{
		forks_destroy(*forks, conf->philo_num);
		return (1);
	}
	if (pthread_mutex_init(&conf->mutex_stdout, NULL) != 0)
	{
		forks_destroy(*forks, conf->philo_num);
		free(*philos);
		return (1);
	}
	conf->all_alive = true;
	return (0);
}

int			main(int argc, char **argv)
{
	t_philo_conf	conf;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (!parse_args((t_philo_args*)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0)
		return (0);
	if (st_setup(&conf, &philos, &forks) != 0)
		return (1);
	if (!philos_start(philos, conf.philo_num))
	{
		forks_destroy(forks, conf.philo_num);
		free(philos);
		return (1);
	}
	while (conf.all_alive)
		;
	philos_detach(philos, conf.philo_num);
	forks_destroy(forks, conf.philo_num);
	pthread_mutex_destroy(&conf.mutex_stdout);
	free(philos);
	return (0);
}
