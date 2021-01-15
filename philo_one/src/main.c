/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:53:02 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/15 22:40:50 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	st_destroy(
	t_philo_conf *conf,
	t_philo *philos,
	pthread_mutex_t *mutex_stdout,
	pthread_mutex_t *mutex_meal_num_finished_counter)
{
	philos_destroy(philos, conf->philo_num);
	forks_destroy(conf->forks, conf->philo_num);
	if (mutex_stdout != NULL)
		pthread_mutex_destroy(mutex_stdout);
	if (mutex_meal_num_finished_counter != NULL)
		pthread_mutex_destroy(mutex_meal_num_finished_counter);
	return (1);
}

static void	*st_routine_flush(t_philo_conf *conf)
{
	pthread_mutex_unlock(&conf->mutex_stdout); // ???????????????
	while (true)
	{
		pthread_mutex_lock(&conf->mutex_stdout);
		philo_put_flush();
		pthread_mutex_unlock(&conf->mutex_stdout);
		usleep(250000);
	}
	return (NULL);
}

static int	st_setup(
	t_philo_conf *conf,
	t_philo **philos)
{
	pthread_t	thread_flush;

	if ((conf->forks = forks_new(conf->philo_num)) == NULL)
		return (1);
	if ((*philos = philos_new(conf)) == NULL)
		return (st_destroy(conf, NULL, NULL, NULL));
	if (pthread_mutex_init(&conf->mutex_stdout, NULL) != 0)
		return (st_destroy(conf, *philos, NULL, NULL));
	if (pthread_create(&thread_flush, NULL,
				(t_routine)st_routine_flush, (void*)&conf) != 0)
		return (st_destroy(conf, *philos, &conf->mutex_stdout, NULL));
	pthread_detach(thread_flush);
	if (pthread_mutex_init(&conf->mutex_meal_num_finished_counter, NULL) != 0)
		return (st_destroy(conf, *philos, &conf->mutex_stdout, NULL));
	conf->all_alive = true;
	conf->meal_num_finished_counter = 0;
	return (0);
}

int			main(int argc, char **argv)
{
	t_philo_conf	conf;
	t_philo			*philos;

	if (!parse_args((t_philo_args*)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0 || conf.meal_num == 0)
		return (0);
	if (st_setup(&conf, &philos) != 0)
		return (1);
	conf.initial_time = h_time_now();
	if (!philos_start(philos, conf.philo_num))
	{
		return (st_destroy(&conf, philos,
				&conf.mutex_stdout, &conf.mutex_meal_num_finished_counter));
	}
	while (!philo_finished(&conf))
		usleep(500);
	philo_put_flush();
	st_destroy(&conf, philos,
		&conf.mutex_stdout, &conf.mutex_meal_num_finished_counter);
	return (0);
}
