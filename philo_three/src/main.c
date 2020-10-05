/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:45:24 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/05 14:31:39 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

sem_t	*philo_sem_create(char *name, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0700, value);
	if (sem == SEM_FAILED)
		return (NULL);
	return (sem);
}

int		main(int argc, char **argv)
{
	t_philo_args	args;
	t_philo			philo;
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_dead;
	pid_t			*pids;
	int				i;

	if (!parse_args(&args, argc, argv))
		return (1);
	if ((forks = philo_sem_create(PHILO_SEM_NAME, args.philo_num)) == NULL
		|| (sem_stdout = philo_sem_create(PHILO_SEM_STDOUT_NAME, 1)) == NULL
		|| (sem_dead = philo_sem_create(PHILO_SEM_DEAD_NAME, 0)) == NULL)
		return (1);
	if ((pids = malloc(sizeof(pid_t) * args.philo_num)) == NULL)
		return (1);
	i = -1;
	while (++i < args.philo_num)
	{
		philo.conf = &args;
		philo.id = i + 1;
		if ((pids[i] = child_start(&philo)) == -1)
		{
			free(pids);
			return (1);
		}
	}
	sem_wait(sem_dead);
	i = -1;
	while (++i < args.philo_num)
		kill(pids[i], SIGKILL);
	free(pids);
	sem_close(forks);
	sem_close(sem_stdout);
	sem_close(sem_dead);
	sem_unlink(PHILO_SEM_NAME);
	sem_unlink(PHILO_SEM_STDOUT_NAME);
	sem_unlink(PHILO_SEM_DEAD_NAME);
	return (0);
}
