/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:45:23 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 13:39:54 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

#define PHILO_SEM_NAME          "semaphore_philo_two"
#define PHILO_SEM_STDOUT_NAME   "semaphore_philo_two_stdout"
#define PHILO_SEM_FINISH_NAME   "semaphore_philo_two_finish"
#define PHILO_SEM_START_NAME    "semaphore_philo_two_start"
#define PHILO_SEM_GRAB_NAME     "semaphore_philo_two_grab"
#define PHILO_SEM_MEAL_NUM_NAME "semaphore_philo_two_meal_num"

static int	st_destroy(t_philo *philos, long int philo_num)
{
	sem_unlink(PHILO_SEM_NAME);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_unlink(PHILO_SEM_FINISH_NAME);
	sem_unlink(PHILO_SEM_MEAL_NUM_NAME);
	sem_unlink(PHILO_SEM_START_NAME);
	sem_unlink(PHILO_SEM_GRAB_NAME);
	while (philo_num-- > 0)
		sem_unlink(philo_sem_eat_name(
				PHILO_SEM_EAT_PREFIX, philos[philo_num].id));
	free(philos);
	return (1);
}

static bool	st_sem_create(const char *name, unsigned int value, sem_t **sem)
{
	sem_unlink(name);
	return ((*sem = sem_open(name, O_CREAT | O_EXCL, 0700, value))
			!= SEM_FAILED);
}

static int	st_setup(t_philo_conf *conf, t_philo **philos)
{
	if (!st_sem_create(PHILO_SEM_NAME, conf->philo_num, &conf->sem_forks) ||
		!st_sem_create(PHILO_SEM_STDOUT_NAME, 1, &conf->sem_stdout) ||
		!st_sem_create(PHILO_SEM_FINISH_NAME, 1, &conf->sem_finish) ||
		!st_sem_create(PHILO_SEM_START_NAME,
			conf->philo_num, &conf->sem_start) ||
		!st_sem_create(PHILO_SEM_GRAB_NAME, 1, &conf->sem_grab) ||
		!st_sem_create(PHILO_SEM_MEAL_NUM_NAME,
			conf->philo_num, &conf->sem_meal_num))
		return (st_destroy(NULL, 0));
	if ((*philos = routine_create_philos(conf)) == NULL)
		return (st_destroy(NULL, 0));
	return (0);
}

static int	st_start(t_philo_conf *conf, t_philo *philos)
{
	long int	i;
	pthread_t	thread;

	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_start);
	i = -1;
	while (++i < conf->philo_num)
	{
		if (pthread_create(&thread, NULL,
				(t_routine)routine_philo, philos + i) != 0)
			return (st_destroy(philos, conf->philo_num));
		pthread_detach(thread);
	}
	conf->initial_time = h_time_now();
	i = -1;
	while (++i < conf->philo_num)
		sem_post(conf->sem_start);
	return (0);
}

int			main(int argc, char **argv)
{
	t_philo_conf	conf;
	t_philo			*philos;
	pthread_t		thread_flush;
	pthread_t		thread_meal_num;

	if (!parse_args((t_philo_args *)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0 || conf.meal_num == 0)
		return (0);
	if (st_setup(&conf, &philos) != 0 || st_start(&conf, philos) != 0)
		return (1);
	if (pthread_create(&thread_flush, NULL,
			(t_routine)routine_flush, &conf) != 0)
		return (st_destroy(philos, conf.philo_num));
	pthread_detach(thread_flush);
	if (pthread_create(&thread_meal_num, NULL,
			(t_routine)routine_meal_num, &conf) != 0)
		return (st_destroy(philos, conf.philo_num));
	pthread_detach(thread_meal_num);
	sem_wait(conf.sem_finish);
	sem_wait(conf.sem_finish);
	philo_put_flush();
	st_destroy(philos, conf.philo_num);
	return (0);
}
