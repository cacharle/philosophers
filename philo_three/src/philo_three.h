/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:46:26 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 14:47:49 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

# include "common.h"

# define PHILO_SEM_NAME        "semaphore_philo_three"
# define PHILO_SEM_STDOUT_NAME "semaphore_philo_three_stdout"
# define PHILO_SEM_ALIVE_NAME  "semaphore_philo_three_alive"

typedef struct
{
	long int		philo_num;
	t_time 			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	long int		meal_num;

}	t_philo_conf;

pid_t	child_start(t_philo_args *arg);

void	event_take_fork(t_philo *arg);
void	event_eat(t_philo *arg);
void	event_think(t_philo *arg);
void	event_sleep(t_philo *arg);
void	event_die(t_philo *arg);

#endif
