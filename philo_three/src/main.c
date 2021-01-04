/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:45:24 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/04 11:06:41 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static sem_t	*st_sem_create(char *name, unsigned int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0700, value));
}

static int		st_destroy(t_sems *sems, pid_t *pids, int philo_num)
{
	int	i;

	if (pids != NULL)
	{
		i = -1;
		while (++i < philo_num)
			kill(pids[i], SIGKILL);
		free(pids);
	}
	sem_close(sems->forks);
	sem_unlink(PHILO_SEM_NAME);
	sem_close(sems->sem_stdout);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_close(sems->sem_finish);
	sem_unlink(PHILO_SEM_FINISH_NAME);
	sem_close(sems->sem_start);
	sem_unlink(PHILO_SEM_START_NAME);
	return (1);
}

static int		st_setup(
		t_philo_args *args, t_sems *sems, pid_t **pids, t_time initial_time)
{
	t_philo	philo;
	int		i;

	sems->sem_stdout = SEM_FAILED;
	sems->sem_finish = SEM_FAILED;
	sems->sem_start = SEM_FAILED;
	if ((sems->forks =
			st_sem_create(PHILO_SEM_NAME, args->philo_num)) == SEM_FAILED
		|| (sems->sem_stdout =
			st_sem_create(PHILO_SEM_STDOUT_NAME, 1)) == SEM_FAILED
		|| (sems->sem_finish =
			st_sem_create(PHILO_SEM_FINISH_NAME,
				args->meal_num == -1 ? 1 : args->philo_num)) == SEM_FAILED
		|| (sems->sem_start =
			st_sem_create(PHILO_SEM_START_NAME, args->philo_num)) == SEM_FAILED
		|| (*pids = malloc(sizeof(pid_t) * args->philo_num)) == NULL)
		return (st_destroy(sems, *pids, 0));
	i = -1;
	while (++i < args->philo_num)
		sem_wait(sems->sem_start);
	i = -1;
	while (++i < args->philo_num)
	{
		philo.conf = args;
		philo.id = i + 1;
		philo.initial_time = initial_time;
		if (((*pids)[i] = child_start(&philo)) == -1)
			return (st_destroy(sems, *pids, i));
	}
	i = -1;
	while (++i < args->philo_num)
		sem_post(sems->sem_start);
	return (0);
}

static void		st_wait(t_philo_args *args, t_sems *sems)
{
	long int		i;

	if (args->meal_num == -1)
	{
		sem_wait(sems->sem_finish);
		sem_wait(sems->sem_finish);
	}
	else
	{
		i = -1;
		while (++i < args->philo_num)
			sem_wait(sems->sem_finish);
		i = -1;
		while (++i < args->philo_num)
			sem_wait(sems->sem_finish);
	}
}

int				main(int argc, char **argv)
{
	t_philo_args	args;
	t_sems			sems;
	pid_t			*pids;

	if (!parse_args(&args, argc, argv))
		return (1);
	if (args.philo_num == 0 || args.meal_num == 0)
		return (0);
	pids = NULL;
	if (st_setup(&args, &sems, &pids, h_time_now()) != 0)
		return (1);
	st_wait(&args, &sems);
	st_destroy(&sems, pids, args.philo_num);
	return (0);
}
