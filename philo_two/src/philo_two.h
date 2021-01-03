/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:47:23 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/03 13:55:04 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# define _XOPEN_SOURCE 500
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>

# include "common.h"

typedef struct
{
	long int		philo_num;
	t_time			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	long int		meal_num;
	t_time			initial_time;
	sem_t			*sem_stdout;
	sem_t			*sem_finish;
}					t_philo_conf;

typedef struct
{
	long int		id;
	t_philo_conf	*conf;
	t_time			time_last_eat;
	sem_t			*forks;
}					t_philo;

/*
** routine.c
*/

void				*routine_philo(t_philo *arg);
void				*routine_death(t_philo *arg);
t_philo				*routine_create_philos(t_philo_conf *conf, sem_t *forks);

/*
** io.c
*/

void				event_take_fork(t_philo *arg);
void				event_eat(t_philo *arg);
void				event_think(t_philo *arg);
void				event_sleep(t_philo *arg);
void				event_die(t_philo *arg);

#endif
