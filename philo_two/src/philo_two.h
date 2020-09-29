/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:47:23 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/29 15:21:32 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <semaphore.h>
// # include "common.h"

typedef struct
{
	int				id;
	t_philo_args	*args;
	t_time			time_last_eat;
	sem_t			*forks;
}					t_routine_arg;

/*
** routine.c
*/

void			*routine_philo(void *void_arg);
void			*routine_death(void *void_arg);
t_routine_arg	*routine_args_create(t_philo_args *philo_args, sem_t *forks);

/*
** io.c
*/

void			io_eat(t_routine_arg *arg);
void			io_think(t_routine_arg *arg);
void			io_sleep(t_routine_arg *arg);
void			io_die(t_routine_arg *arg);

#endif
