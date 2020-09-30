/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:47:23 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 08:41:15 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>

# include "common.h"

typedef struct
{
	long int		philo_num;
	t_time 			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	long int		meal_num;
	bool			all_alive;
	pthread_mutex_t	mutex_all_alive;
	pthread_mutex_t	mutex_stdout;
}					t_philo_conf;

typedef struct
{
	int				id;
	t_philo_conf	*conf;
	t_time			time_last_eat;
	sem_t			*forks;
}					t_routine_arg;

/*
** routine.c
*/

void			*routine_philo(t_routine_arg *arg);
void			*routine_death(t_routine_arg *arg);
t_routine_arg	*routine_args_create(t_philo_conf *conf, sem_t *forks);

/*
** io.c
*/

void			io_take_fork(t_routine_arg *arg);
void			io_eat(t_routine_arg *arg);
void			io_think(t_routine_arg *arg);
void			io_sleep(t_routine_arg *arg);
void			io_die(t_routine_arg *arg);

#endif
