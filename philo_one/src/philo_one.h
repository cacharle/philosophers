/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:11:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 07:48:36 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>

# include "common.h"

// typedef long int	t_time;

// typedef enum
// {
// 	EVENT_FORK,
// 	EVENT_EAT,
// 	EVENT_SLEEP,
// 	EVENT_THINK,
// 	EVENT_DIE
// }					t_philo_event;

typedef struct
{
	t_philo_args	args;
	bool			all_alive;
	pthread_mutex_t	mutex_stdout;
	pthread_mutex_t	mutex_all_alive;
}					t_philo_conf;

typedef struct		s_philo
{
	int				id;
	bool			alive;
	t_time			time_last_eat;
	pthread_t		thread;
}					t_philo;

typedef struct		s_routine_arg
{
	t_philo_conf	*conf;
	t_philo			*philo;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*mutex_stdout;
}					t_routine_arg;

/*
** forks.c
*/

pthread_mutex_t			*forks_new(int num);
void					forks_destroy(pthread_mutex_t *forks, int num);
t_routine_arg			*forks_dispatch(
							t_philo *philos,
							pthread_mutex_t *forks,
							t_philo_conf *conf);

/*
** philo.c
*/

t_philo					*philos_new(int num);
void					philos_destroy(t_philo *philos, int num);
bool					philos_start(
							t_philo *philos,
							t_routine_arg *routine_args,
							int num);
void					philos_detach(t_philo *philos, int num);

/*
** routine.c
*/

void					*routine_philo(t_routine_arg *arg);
void					*routine_death(t_routine_arg *arg);

/*
** io.c
*/

void					io_eat(t_routine_arg *arg);
void					io_think(t_routine_arg *arg);
void					io_sleep(t_routine_arg *arg);
void					io_die(t_routine_arg *arg);

#endif
