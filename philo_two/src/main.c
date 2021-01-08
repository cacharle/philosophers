/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:45:23 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/08 20:16:20 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

#define PHILO_SEM_NAME        "semaphore_philo_two"
#define PHILO_SEM_STDOUT_NAME "semaphore_philo_two_stdout"
#define PHILO_SEM_FINISH_NAME "semaphore_philo_two_finish"
#define PHILO_SEM_START_NAME  "semaphore_philo_two_start"
#define PHILO_SEM_GRAB_NAME   "semaphore_philo_two_grab"

static int	st_destroy(
	t_philo *philos,
	pthread_t *threads)
{
	sem_unlink(PHILO_SEM_NAME);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_unlink(PHILO_SEM_FINISH_NAME);
	sem_unlink(PHILO_SEM_START_NAME);
	sem_unlink(PHILO_SEM_GRAB_NAME);
	free(philos);
	free(threads);
	return (1);
}

static bool	st_sem_create(const char *name, unsigned int value, sem_t **sem)
{
	sem_unlink(name);
	return ((*sem = sem_open(name, O_CREAT | O_EXCL, 0700, value))
			!= SEM_FAILED);
}

void		*routine_flush(t_philo_conf *conf)
{
	while (true)
	{
		sem_wait(conf->sem_stdout);
		philo_put_flush();
		sem_post(conf->sem_stdout);
		usleep(250000);
	}
}

static int	st_setup(
	t_philo_conf *conf,
	t_philo **philos,
	sem_t **forks,
	pthread_t **threads)
{
	long int	i;

	if (!st_sem_create(PHILO_SEM_NAME, conf->philo_num, forks) ||
		!st_sem_create(PHILO_SEM_STDOUT_NAME, 1, &conf->sem_stdout) ||
		!st_sem_create(PHILO_SEM_FINISH_NAME,
			conf->meal_num == -1 ? 1 : conf->philo_num, &conf->sem_finish) ||
		!st_sem_create(PHILO_SEM_START_NAME, conf->philo_num, &conf->sem_start) ||
		!st_sem_create(PHILO_SEM_GRAB_NAME, 1, &conf->sem_grab))
		return (1);
	*threads = NULL;
	if ((*philos = routine_create_philos(conf, *forks)) == NULL ||
		(*threads = malloc(sizeof(pthread_t) * conf->philo_num)) == NULL)
		return (st_destroy(*philos, *threads));
	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_start);
	i = -1;
	while (++i < conf->philo_num)
	{
		if (pthread_create(*threads + i, NULL,
				(t_routine)routine_philo, *philos + i) != 0)
		{
			while (--i >= 0)
				pthread_detach((*threads)[i]);
			return (st_destroy(*philos, *threads));
		}
	}
	conf->initial_time = h_time_now();
	i = -1;
	while (++i < conf->philo_num)
		sem_post(conf->sem_start);
	return (0);
}

static void	st_wait(t_philo_conf *conf)
{
	long int	i;

	if (conf->meal_num == -1)
	{
		sem_wait(conf->sem_finish);
		sem_wait(conf->sem_finish);
	}
	else
	{
		i = -1;
		while (++i < conf->philo_num)
			sem_wait(conf->sem_finish);
		i = -1;
		while (++i < conf->philo_num)
			sem_wait(conf->sem_finish);
	}
}

int			main(int argc, char **argv)
{
	long int		i;
	t_philo_conf	conf;
	t_philo			*philos;
	sem_t			*forks;
	pthread_t		*threads;

	if (!parse_args((t_philo_args *)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0 || conf.meal_num == 0)
		return (0);
	if (st_setup(&conf, &philos, &forks, &threads) != 0)
		return (1);
	pthread_t thread_flush;
	pthread_create(&thread_flush, NULL, (t_routine)routine_flush, (void*)&conf);
	pthread_detach(thread_flush);
	st_wait(&conf);
	philo_put_flush();
	i = -1;
	while (++i < conf.philo_num)
		pthread_detach(threads[i]);
	st_destroy(philos, threads);
	return (0);
}
