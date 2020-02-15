/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:11:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/15 01:25:40 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include "common.h"

typedef pthread_mutex_t	t_fork;

typedef struct			s_philo
{
	int					id;
	t_bool				alive;
	t_time				time_last_eat;
	t_philo_state		state;
	pthread_t			thread;
}						t_philo;

typedef struct			s_routine_arg
{
	t_philo_args		*args;
	t_philo				*philo;
	t_fork				*fork_left;
	t_fork				*fork_right;
	pthread_mutex_t		*mutex_stdout;
}						t_routine_arg;

/*
** fork.c
*/

t_fork					*forks_new(int num);
void					forks_destroy(t_fork *forks, int num);
t_routine_arg			*forks_dispatch(t_philo *philos,
										t_fork *forks, t_philo_args *args);

/*
** philo.c
*/

t_philo					*philos_new(int num);
void					philos_destroy(t_philo *philos, int num);
t_bool					philos_start(t_philo *philos,
										t_routine_arg *routine_args, int num);
void					philos_join(t_philo *philos, int num);
t_bool					philos_starved(t_philo *philos, int num);

/*
** routine.c
*/

void					*routine_philo(void *void_arg);
void					*routine_death(void *void_arg);

/*
** io.c
*/

void					io_eat(t_routine_arg *arg);
void					io_think(t_routine_arg *arg);
void					io_sleep(t_routine_arg *arg);
void					io_die(t_routine_arg *arg);

#endif
