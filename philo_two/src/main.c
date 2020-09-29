/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:45:23 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/29 15:27:05 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int main(int argc, char **argv)
{
	int				i;
	t_philo_args	philo_args;
	t_routine_arg	*routine_args;
	sem_t			*forks;
	pthread_t		*threads;

	if (!parse_args(&philo_args, argc, argv))
		return (1);
	sem_unlink("philo_two");
	forks = sem_open("philo_two", O_CREAT, 0700, philo_args.philo_num);
	if (forks == SEM_FAILED)
		return (1);
	if ((routine_args = routine_args_create(&philo_args, forks)) == NULL)
		return (1);
	if ((threads = malloc(sizeof(pthread_t) * philo_args.philo_num)) == NULL)
		return (1);
	philo_args.all_alive = TRUE;
	pthread_mutex_init(&philo_args.mutex_all_alive, NULL);
	pthread_mutex_init(&philo_args.mutex_stdout, NULL);

	i = -1;
	while (++i < philo_args.philo_num)
		if (pthread_create(threads + i, NULL, routine_philo, routine_args + i) < 0)
			return (1);
	while (philo_args.all_alive)
		;

	i = -1;
	while (++i < philo_args.philo_num)
		pthread_join(threads[i], NULL);
	sem_close(forks);
	sem_unlink("philo_two");

	pthread_mutex_destroy(&philo_args.mutex_stdout);
	pthread_mutex_destroy(&philo_args.mutex_all_alive);
	free(threads);
	free(routine_args);
	return (0);
}
