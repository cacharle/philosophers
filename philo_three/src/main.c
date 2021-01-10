/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:45:24 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 14:25:49 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	st_destroy(t_philo_conf *conf, pid_t *pids, long int philo_num)
{
	long int	i;

	if (pids != NULL)
	{
		i = -1;
		while (++i < philo_num)
			kill(pids[i], SIGKILL);
		free(pids);
	}
	h_destroy_sem(PHILO_SEM_NAME, conf->forks);
	h_destroy_sem(PHILO_SEM_STDOUT_NAME, conf->sem_stdout);
	h_destroy_sem(PHILO_SEM_FINISH_NAME, conf->sem_finish);
	h_destroy_sem(PHILO_SEM_MEAL_NUM_NAME, conf->sem_meal_num);
	h_destroy_sem(PHILO_SEM_START_NAME, conf->sem_start);
	h_destroy_sem(PHILO_SEM_GRAB_NAME, conf->sem_grab);
	return (1);
}

static int	st_setup(t_philo_conf *conf, pid_t **pids)
{
	conf->forks = SEM_FAILED;
	conf->sem_stdout = SEM_FAILED;
	conf->sem_finish = SEM_FAILED;
	conf->sem_meal_num = SEM_FAILED;
	conf->sem_start = SEM_FAILED;
	conf->sem_grab = SEM_FAILED;
	*pids = NULL;
	if (!h_sem_create(PHILO_SEM_NAME, conf->philo_num, &conf->forks) ||
		!h_sem_create(PHILO_SEM_STDOUT_NAME, 1, &conf->sem_stdout) ||
		!h_sem_create(PHILO_SEM_FINISH_NAME, 1, &conf->sem_finish) ||
		!h_sem_create(PHILO_SEM_MEAL_NUM_NAME,
			conf->philo_num, &conf->sem_meal_num) ||
		!h_sem_create(PHILO_SEM_START_NAME,
			conf->philo_num, &conf->sem_start) ||
		!h_sem_create(PHILO_SEM_GRAB_NAME, 1, &conf->sem_grab) ||
		(*pids = malloc(sizeof(pid_t) * conf->philo_num)) == NULL)
		return (1);
	return (0);
}

static int	st_start(t_philo_conf *conf, pid_t *pids, t_time initial_time)
{
	t_philo		philo;
	long int	i;

	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_start);
	i = -1;
	while (++i < conf->philo_num)
	{
		philo.conf = conf;
		philo.id = i + 1;
		philo.initial_time = initial_time;
		if ((pids[i] = child_start(&philo)) == -1)
			return (1);
	}
	i = -1;
	while (++i < conf->philo_num)
		sem_post(conf->sem_start);
	return (0);
}

static void	*st_routine_meal_num(t_philo_conf *conf)
{
	long int	i;

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

int			main(int argc, char **argv)
{
	t_philo_conf	conf;
	pid_t			*pids;
	pthread_t		thread_meal_num;

	if (!parse_args((t_philo_args*)&conf, argc, argv))
		return (1);
	if (conf.philo_num == 0 || conf.meal_num == 0)
		return (0);
	if (st_setup(&conf, &pids) != 0 || st_start(&conf, pids, h_time_now()) != 0)
		return (st_destroy(&conf, pids, conf.philo_num));
	if (conf.meal_num != -1)
	{
		if (pthread_create(&thread_meal_num,
					NULL, (t_routine)st_routine_meal_num, &conf) != 0)
			return (st_destroy(&conf, pids, conf.philo_num));
		pthread_detach(thread_meal_num);
	}
	sem_wait(conf.sem_finish);
	sem_wait(conf.sem_finish);
	st_destroy(&conf, pids, conf.philo_num);
	return (0);
}
