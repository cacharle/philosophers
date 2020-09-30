/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:45:23 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 09:58:01 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

#define PHILO_SEM_NAME "semaphore_philo_two"

int main(int argc, char **argv)
{
	int				i;
	t_philo_conf	conf;
	t_philo			*philos;
	sem_t			*forks;
	pthread_t		*threads;

	if (!parse_args((t_philo_args*)&conf, argc, argv))
		return (1);
	sem_unlink(PHILO_SEM_NAME);
	forks = sem_open(PHILO_SEM_NAME, O_CREAT | O_EXCL, 0600, conf.philo_num);
	if (forks == SEM_FAILED)
		return (1);
	if ((philos = routine_create_philos(&conf, forks)) == NULL)
		return (1);
	if ((threads = malloc(sizeof(pthread_t) * conf.philo_num)) == NULL)
		return (1);
	conf.all_alive = true;
	pthread_mutex_init(&conf.mutex_stdout, NULL);

	i = -1;
	while (++i < conf.philo_num)
		if (pthread_create(threads + i, NULL, (t_routine)routine_philo, philos + i) < 0)
			return (1);
	while (conf.all_alive)
		;

	i = -1;
	while (++i < conf.philo_num)
		pthread_detach(threads[i]);
	sem_close(forks);
	sem_unlink(PHILO_SEM_NAME);

	pthread_mutex_destroy(&conf.mutex_stdout);
	free(threads);
	free(philos);
	return (0);
}
