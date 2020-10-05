/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:46:26 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/05 15:05:26 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

# include "common.h"

# define PHILO_SEM_NAME        "semaphore_philo_three"
# define PHILO_SEM_STDOUT_NAME "semaphore_philo_three_stdout"
# define PHILO_SEM_DEAD_NAME   "semaphore_philo_three_dead"

typedef struct		s_philo
{
	t_philo_args	*conf;
	int				id;
	t_time			time_last_eat;
	sem_t			*forks;
	sem_t			*sem_stdout;
	sem_t			*sem_dead;
}					t_philo;

pid_t				child_start(t_philo *arg);

void				event_take_fork(t_philo *arg);
void				event_eat(t_philo *arg);
void				event_think(t_philo *arg);
void				event_sleep(t_philo *arg);
void				event_die(t_philo *arg);

#endif
