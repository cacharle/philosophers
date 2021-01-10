/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:46:26 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 14:00:13 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# define _XOPEN_SOURCE 500
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

# include "common.h"

# define PHILO_SEM_NAME          "semaphore_philo_three"
# define PHILO_SEM_STDOUT_NAME   "semaphore_philo_three_stdout"
# define PHILO_SEM_FINISH_NAME   "semaphore_philo_three_finish"
# define PHILO_SEM_MEAL_NUM_NAME "semaphore_philo_three_meal_num"
# define PHILO_SEM_START_NAME    "semaphore_philo_three_start"
# define PHILO_SEM_GRAB_NAME     "semaphore_philo_three_grab"

typedef struct		s_philo_conf
{
	long int		philo_num;
	t_time			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	long int		meal_num;
	t_time			initial_time;
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_finish;
	sem_t			*sem_meal_num;
	sem_t			*sem_start;
	sem_t			*sem_grab;
}					t_philo_conf;

typedef struct		s_philo
{
	t_philo_conf	*conf;
	int				id;
	t_time			time_last_eat;
	t_time			initial_time;
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_finish;
	sem_t			*sem_meal_num;
	sem_t			*sem_start;
	sem_t			*sem_grab;
	sem_t			*sem_eat;
}					t_philo;

/*
** child.c
*/

pid_t				child_start(t_philo *arg);

/*
** event.c
*/

void				event_take_fork(t_philo *arg);
void				event_eat(t_philo *arg);
void				event_think(t_philo *arg);
void				event_sleep(t_philo *arg);
void				event_die(t_philo *arg);

/*
** helper.c
*/

void				h_destroy_sem(const char *name, sem_t *sem);
bool				h_sem_create(
						const char *name, unsigned int value, sem_t **sem);

#endif
