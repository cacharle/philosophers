/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:45:23 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/01 15:57:40 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

#define PHILO_SEM_NAME                           "semaphore_philo_two"
#define PHILO_SEM_STDOUT_NAME                    "semaphore_philo_two_stdout"
#define PHILO_SEM_MEAL_NUM_FINISHED_COUNTER_NAME "semaphore_philo_two_meal_num"

static int	st_destroy(
	sem_t *forks,
	t_philo *philos,
	pthread_t *threads,
	t_philo_conf *conf)
{
	/* int	i; */
    /*  */
	/* i = -1; */
	/* while (++i < conf->philo_num) */
	/* 	sem_post(forks); */
	sem_close(forks);
	sem_unlink(PHILO_SEM_NAME);
	sem_close(conf->sem_stdout);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_close(conf->sem_meal_num_finished_counter);
	sem_unlink(PHILO_SEM_MEAL_NUM_FINISHED_COUNTER_NAME);
	free(philos);
	free(threads);
	return (1);
}

static sem_t	*st_sem_create(const char *name, unsigned int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0700, value));
}

static int	st_setup(
	t_philo_conf *conf,
	t_philo **philos,
	sem_t **forks,
	pthread_t **threads)
{
	long int	i;

	*forks = st_sem_create(PHILO_SEM_NAME, conf->philo_num);
	if (*forks == SEM_FAILED)
		return (1);
	conf->sem_stdout = st_sem_create(PHILO_SEM_STDOUT_NAME, 1);
	if (conf->sem_stdout == SEM_FAILED)
		return (1);
	conf->sem_meal_num_finished_counter = st_sem_create(PHILO_SEM_MEAL_NUM_FINISHED_COUNTER_NAME, 1);
	if (conf->sem_meal_num_finished_counter == SEM_FAILED)
		return (1);
	*threads = NULL;
	if ((*philos = routine_create_philos(conf, *forks)) == NULL ||
		(*threads = malloc(sizeof(pthread_t) * conf->philo_num)) == NULL)
		return (st_destroy(*forks, *philos, *threads, conf));
	conf->all_alive = true;
	conf->meal_num_finished_counter = 0;
	i = -1;
	while (++i < conf->philo_num)
	{
		if (pthread_create(*threads + i, NULL,
				(t_routine)routine_philo, *philos + i) != 0)
		{
			while (--i >= 0)
				pthread_detach((*threads)[i]);
			return (st_destroy(*forks, *philos, *threads, conf));
		}
		usleep(200);
	}
	return (0);
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
	while (!philo_finished(&conf))
		;
	conf.all_alive = false;
	i = -1;
	while (++i < conf.philo_num)
		pthread_detach(threads[i]);
	st_destroy(forks, philos, threads, &conf);
	return (0);
}
