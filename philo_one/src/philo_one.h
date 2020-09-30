/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:11:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 09:50:02 by cacharle         ###   ########.fr       */
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

/*
** t_philo_args with more fields at the end
*/

typedef struct
{
	long int		philo_num;
	t_time 			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	long int		meal_num;
	bool			all_alive;
	pthread_mutex_t	mutex_stdout;
}					t_philo_conf;

typedef struct		s_philo
{
	int				id;
	pthread_t		thread;
	t_time			time_last_eat;
	t_philo_conf	*conf;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*mutex_stdout;
}					t_philo;

/*
** forks.c
*/

pthread_mutex_t			*forks_new(int num);
void					forks_destroy(pthread_mutex_t *forks, int num);

/*
** philo.c
*/

t_philo					*philos_new(t_philo_conf *conf, pthread_mutex_t *forks);
void					philos_destroy(t_philo *philos, int num);
bool					philos_start(t_philo *philos, int num);
void					philos_detach(t_philo *philos, int num);

/*
** routine.c
*/

void					*routine_philo(t_philo *arg);
void					*routine_death(t_philo *arg);

/*
** io.c
*/

void					io_take_fork(t_philo *arg, pthread_mutex_t *fork);
void					io_eat(t_philo *arg);
void					io_think(t_philo *arg);
void					io_sleep(t_philo *arg, pthread_mutex_t *fork_right, pthread_mutex_t *fork_left);
void					io_die(t_philo *arg);

#endif
