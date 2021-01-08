/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:46:26 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/08 20:25:00 by charles          ###   ########.fr       */
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

# define PHILO_SEM_NAME        "semaphore_philo_three"
# define PHILO_SEM_STDOUT_NAME "semaphore_philo_three_stdout"
# define PHILO_SEM_FINISH_NAME "semaphore_philo_three_finish"
# define PHILO_SEM_START_NAME  "semaphore_philo_three_start"
# define PHILO_SEM_GRAB_NAME   "semaphore_philo_three_grab"

typedef struct		s_philo
{
	t_philo_args	*conf;
	int				id;
	t_time			time_last_eat;
	t_time			initial_time;
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_finish;
	sem_t			*sem_start;
	sem_t			*sem_grab;
}					t_philo;

typedef struct		s_sems
{
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_finish;
	sem_t			*sem_start;
	sem_t			*sem_grab;
}					t_sems;

pid_t				child_start(t_philo *arg);

void				event_take_fork(t_philo *arg);
void				event_eat(t_philo *arg);
void				event_think(t_philo *arg);
void				event_sleep(t_philo *arg);
void				event_die(t_philo *arg);

#endif
