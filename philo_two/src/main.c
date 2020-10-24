/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:45:23 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/24 13:02:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

#define PHILO_SEM_NAME        "semaphore_philo_two"
#define PHILO_SEM_STDOUT_NAME "semaphore_philo_two_stdout"

static int	st_destroy(
	sem_t *forks,
	t_philo *philos,
	pthread_t *threads,
	t_philo_conf *conf)
{
	int	i;

	i = -1;
	while (++i < conf->philo_num)
		sem_post(forks);
	sem_close(forks);
	sem_unlink(PHILO_SEM_NAME);
	sem_close(conf->sem_stdout);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	free(philos);
	free(threads);
	return (1);
}

static int	st_setup(
	t_philo_conf *conf,
	t_philo **philos,
	sem_t **forks,
	pthread_t **threads)
{
	int	i;

	sem_unlink(PHILO_SEM_NAME);
	*forks = sem_open(PHILO_SEM_NAME, O_CREAT | O_EXCL, 0700, conf->philo_num);
	if (*forks == SEM_FAILED)
		return (1);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	conf->sem_stdout = sem_open(PHILO_SEM_STDOUT_NAME, O_CREAT | O_EXCL, 0700, 1);
	if (conf->sem_stdout == SEM_FAILED)
		return (1);
	*threads = NULL;
	if ((*philos = routine_create_philos(conf, *forks)) == NULL ||
		(*threads = malloc(sizeof(pthread_t) * conf->philo_num)) == NULL)
		return (st_destroy(*forks, *philos, *threads, conf));
	conf->all_alive = true;
	i = -1;
	while (++i < conf->philo_num)
		if (pthread_create(*threads + i, NULL,
				(t_routine)routine_philo, *philos + i) != 0)
		{
			while (--i >= 0)
				pthread_detach((*threads)[i]);
			return (st_destroy(*forks, *philos, *threads, conf));
		}
	return (0);
}

int			main(int argc, char **argv)
{
	int				i;
	t_philo_conf	conf;
	t_philo			*philos;
	sem_t			*forks;
	pthread_t		*threads;

	if (!parse_args((t_philo_args *)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0)
		return (0);
	if (st_setup(&conf, &philos, &forks, &threads) != 0)
		return (1);
	while (conf.all_alive)
		;
	i = -1;
	while (++i < conf.philo_num)
		pthread_detach(threads[i]);
	st_destroy(forks, philos, threads, &conf);
	return (0);
}
