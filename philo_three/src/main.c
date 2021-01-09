/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:45:24 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/09 15:57:47 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static sem_t	*st_sem_create(char *name, unsigned int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0700, value));
}

static int		st_destroy(t_philo_conf *conf, pid_t *pids, int philo_num)
{
	int	i;

	if (pids != NULL)
	{
		i = -1;
		while (++i < philo_num)
			kill(pids[i], SIGKILL);
		free(pids);
	}
	sem_close(conf->forks);
	sem_unlink(PHILO_SEM_NAME);
	sem_close(conf->sem_stdout);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_close(conf->sem_finish);
	sem_unlink(PHILO_SEM_FINISH_NAME);
	sem_close(conf->sem_meal_num);
	sem_unlink(PHILO_SEM_MEAL_NUM_NAME);
	sem_close(conf->sem_start);
	sem_unlink(PHILO_SEM_START_NAME);
	sem_close(conf->sem_grab);
	sem_unlink(PHILO_SEM_GRAB_NAME);
	return (1);
}

/* static bool	st_sem_create(const char *name, unsigned int value, sem_t **sem) */
/* { */
/* 	sem_unlink(name); */
/* 	return ((*sem = sem_open(name, O_CREAT | O_EXCL, 0700, value)) */
/* 			!= SEM_FAILED); */
/* } */

static int		st_setup(
		t_philo_conf *conf, pid_t **pids, t_time initial_time)
{
	t_philo	philo;
	int		i;

	conf->sem_stdout = SEM_FAILED;
	conf->sem_finish = SEM_FAILED;
	conf->sem_start = SEM_FAILED;
	if ((conf->forks = st_sem_create(PHILO_SEM_NAME, conf->philo_num)) == SEM_FAILED
		|| (conf->sem_stdout = st_sem_create(PHILO_SEM_STDOUT_NAME, 1)) == SEM_FAILED
		|| (conf->sem_finish = st_sem_create(PHILO_SEM_FINISH_NAME, 1)) == SEM_FAILED
		|| (conf->sem_meal_num = st_sem_create(PHILO_SEM_MEAL_NUM_NAME, conf->philo_num)) == SEM_FAILED
		|| (conf->sem_start = st_sem_create(PHILO_SEM_START_NAME, conf->philo_num)) == SEM_FAILED
		|| (conf->sem_grab = st_sem_create(PHILO_SEM_GRAB_NAME, 1)) == SEM_FAILED
		|| (*pids = malloc(sizeof(pid_t) * conf->philo_num)) == NULL)
		return (st_destroy(conf, *pids, 0));
	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_start);
	i = -1;
	while (++i < conf->philo_num)
	{
		philo.conf = conf;
		philo.id = i + 1;
		philo.initial_time = initial_time;
		if (((*pids)[i] = child_start(&philo)) == -1)
			return (st_destroy(conf, *pids, i));
	}
	i = -1;
	while (++i < conf->philo_num)
		sem_post(conf->sem_start);
	return (0);
}

static void		*st_routine_meal_num(t_philo_conf *conf)
{
	long int		i;

	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_meal_num);
	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_meal_num);
	sem_wait(conf->sem_stdout);
	sem_post(conf->sem_finish);
	return (NULL);
}

int				main(int argc, char **argv)
{
	t_philo_conf	conf;
	pid_t			*pids;

	if (!parse_args((t_philo_args*)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0 || conf.meal_num == 0)
		return (0);
	pids = NULL;
	if (st_setup(&conf, &pids, h_time_now()) != 0)
		return (1);
	if (conf.meal_num != -1)
	{
		pthread_t thread_meal_num;
		pthread_create(&thread_meal_num, NULL, (t_routine)st_routine_meal_num, (void*)&conf);
		pthread_detach(thread_meal_num);
	}
	sem_wait(conf.sem_finish);
	sem_wait(conf.sem_finish);
	st_destroy(&conf, pids, conf.philo_num);
	return (0);
}
