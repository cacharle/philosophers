/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:45:24 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/05 16:59:54 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static sem_t	*st_sem_create(char *name, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0700, value);
	if (sem == SEM_FAILED)
		return (SEM_FAILED);
	return (sem);
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
	sem_close(sems->sem_stdout);
	sem_close(sems->sem_dead);
	sem_unlink(PHILO_SEM_NAME);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_unlink(PHILO_SEM_DEAD_NAME);
	return (1);
}

static int		st_setup(t_philo_args *args, t_sems *sems, pid_t **pids)
{
	t_philo	philo;
	int		i;

	sems->sem_stdout = SEM_FAILED;
	sems->sem_dead = SEM_FAILED;
	*pids = NULL;
	if ((sems->forks =
			st_sem_create(PHILO_SEM_NAME, args->philo_num)) == SEM_FAILED
		|| (sems->sem_stdout =
			st_sem_create(PHILO_SEM_STDOUT_NAME, 1)) == SEM_FAILED
		|| (sems->sem_dead =
			st_sem_create(PHILO_SEM_DEAD_NAME, 1)) == SEM_FAILED
		|| (*pids = malloc(sizeof(pid_t) * args->philo_num)) == NULL)
		return (st_destroy(sems, *pids, 0));
	i = -1;
	while (++i < args->philo_num)
	{
		philo.conf = args;
		philo.id = i + 1;
		if (((*pids)[i] = child_start(&philo)) == -1)
			return (st_destroy(sems, *pids, i));
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_philo_args	args;
	t_sems			sems;
	pid_t			*pids;

	if (!parse_args(&args, argc, argv))
		return (1);
	if (args.philo_num == 0)
		return (0);
	if (st_setup(&args, &sems, &pids) != 0)
		return (1);
	sem_wait(sems.sem_dead);
	sem_wait(sems.sem_dead);
	st_destroy(&sems, pids, args.philo_num);
	return (0);
}
