/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:45:24 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/15 01:40:26 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int main(int argc, char **argv)
{
	t_philo_args	philo_args;
	sem_t			*forks;

	if (!parse_args(&philo_args, argc, argv))
		return (1);
	forks = sem_open("philo_two", O_CREAT, 0700, philo_args.philo_num);
	if (forks == SEM_FAILED)
		return (1);

	i = -1;
	while (++i < philo_args.philo_num)
	{
		pid = fork();	
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			child_start(&philo_args);
			return (0);
		}
	}

	sem_close(forks);
	sem_unlink("philo_two");
	return (0);
}
