/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:58:35 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 00:35:30 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define FALSE 0
# define TRUE 1

typedef int			t_bool;
typedef long int	t_time;

typedef enum
{
	PSTATE_EATING = 0,
	PSTATE_SLEEPING,
	PSTATE_THINKING,
	PSTATE_NUM
}	t_philo_state;

typedef enum
{
	EVENT_FORK,
	EVENT_EATING,
	EVENT_SLEEPING,
	EVENT_THINKING,
	EVENT_DIED
}	t_philo_event;

typedef struct
{
	int				philo_num;
	t_time 			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	int 			meal_num;
}					t_philo_args;

typedef void		(*t_philo_routine)(void *arg);

/*
** common.c
*/

t_bool				parse_args(t_philo_args *philo_args, int argc, char **argv);
void				philo_put_state_change(int id, t_philo_event event);

/*
** philo.c
*/

void				philo_eat(int id, t_time timeout);
void				philo_sleep(int id, t_time timeout);
void				philo_think(int id);
void				philo_die(int id);

/*
** helper.c
*/

long int			h_strtoposint(char *s);
int					h_strlen(char *s);
void				h_putnbr(unsigned long num);
void				h_putchar(char c);
void				h_putstr(char *s);
void				*h_calloc(int count, int size);
t_time				h_timeval_to_time(struct timeval *tp);

#endif
