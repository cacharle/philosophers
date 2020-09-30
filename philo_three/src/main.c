/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:45:24 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 14:45:20 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int main(int argc, char **argv)
{
	t_philo_args	args;
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_dead;

	if (!parse_args(&args, argc, argv))
		return (1);

	sem_unlink(PHILO_SEM_NAME);
	forks = sem_open(PHILO_SEM_NAME, O_CREAT | O_EXCL, 0700, args.philo_num);
	if (forks == SEM_FAILED)
		return (1);

	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_stdout = sem_open(PHILO_SEM_STDOUT_NAME, O_CREAT | O_EXCL, 0700, 1);
	if (sem_stdout == SEM_FAILED)
		return (1);

	sem_unlink(PHILO_SEM_ALIVE_NAME);
	sem_dead = sem_open(PHILO_SEM_ALIVE_NAME, O_CREAT | O_EXCL, 0700, 1);
	if (sem_dead == SEM_FAILED)
		return (1);

	pid_t	pid;
	pid_t	*pids;
	pids = malloc(sizeof(pid_t) * args.philo_num);

	int i = -1;
	while (++i < args.philo_num)
		pids[i] = child_start(&args);

	sem_wait(sem_dead);

	i = -1;
	while (++i < args.philo_num)
		kill(pids[i], SIGKILL);
	free(pids);

	sem_close(forks);
	sem_close(sem_stdout);
	sem_unlink(PHILO_SEM_NAME);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	return (0);
}

