/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:45:23 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 08:44:46 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

#define PHILO_SEM_NAME "philo_two"

int main(int argc, char **argv)
{
	int				i;
	t_philo_conf	conf;
	t_routine_arg	*routine_args;
	sem_t			*forks;
	pthread_t		*threads;

	if (!parse_args((t_philo_args*)&conf, argc, argv))
		return (1);
	sem_unlink(PHILO_SEM_NAME);
	forks = sem_open(PHILO_SEM_NAME, O_CREAT, 0700, conf.philo_num);
	if (forks == SEM_FAILED)
		return (1);
	if ((routine_args = routine_args_create(&conf, forks)) == NULL)
		return (1);
	if ((threads = malloc(sizeof(pthread_t) * conf.philo_num)) == NULL)
		return (1);
	conf.all_alive = true;
	pthread_mutex_init(&conf.mutex_all_alive, NULL);
	pthread_mutex_init(&conf.mutex_stdout, NULL);

	i = -1;
	while (++i < conf.philo_num)
		if (pthread_create(threads + i, NULL, (t_routine)routine_philo, routine_args + i) < 0)
			return (1);
	while (conf.all_alive)
		;

	i = -1;
	while (++i < conf.philo_num)
		pthread_detach(threads[i]);
	sem_close(forks);
	sem_unlink(PHILO_SEM_NAME);

	pthread_mutex_destroy(&conf.mutex_stdout);
	pthread_mutex_destroy(&conf.mutex_all_alive);
	free(threads);
	free(routine_args);
	return (0);
}
