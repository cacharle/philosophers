/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:11:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 01:41:39 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE
# define PHILO_ONE

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include "common.h"

typedef struct
{
	t_bool			used;
	pthread_mutex_t	mutex;
}					t_fork;

// typedef struct
// {
// 	t_philo			*philos;
// 	t_fork			*forks;
// }					t_table;

typedef struct s_philo	t_philo;

typedef struct
{
	t_philo			*watched;
	pthread_t		thread;
}					t_watchdog;

struct				s_philo
{
	int				id;
	t_bool			alive;
	t_watchdog		watchdog;
	t_time			time_last_eat;
	t_philo_state	state;
	pthread_t		thread;
};

typedef struct
{
	t_philo_args	*args;
	t_philo			*philo;
	t_fork			*fork_left;
	t_fork			*fork_right;
	pthread_mutex_t	*mutex_stdout;
}					t_routine_arg;

/*
** fork.c
*/

t_fork			*forks_new(int num);
void			forks_destroy(t_fork *forks, int num);
t_routine_arg	*forks_dispatch(t_philo *philos, t_fork *forks, t_philo_args *args);

/*
** philo.c
*/

t_philo			*philos_new(int num);
void			philos_destroy(t_philo *philos, int num);
t_bool			philos_start(t_philo *philos, t_routine_arg *routine_args, int num);
void			philos_join(t_philo *philos, int num);
t_bool			philos_starved(t_philo *philos, int num);

/*
** routine.c
*/

void			*routine_philo(void *void_arg);
void			*routine_death(void *void_arg);

#endif
