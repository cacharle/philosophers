/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:11:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/04/22 13:26:06 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>

typedef long int	t_time;

typedef enum
{
	EVENT_FORK,
	EVENT_EAT,
	EVENT_SLEEP,
	EVENT_THINK,
	EVENT_DIE
}					t_philo_event;

typedef struct
{
	int				philo_num;
	t_time			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	int				meal_num;
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

typedef void		(*t_philo_routine)(void *arg);

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
void					philos_join(t_philo *philos, int num);
bool					philos_starved(t_philo *philos, int num);

/*
** routine.c
*/

void					*routine_philo(void *void_arg);
void					*routine_death(void *void_arg);

/*
** io.c
*/

void					io_eat(t_routine_arg *arg);
void					io_think(t_routine_arg *arg);
void					io_sleep(t_routine_arg *arg);
void					io_die(t_routine_arg *arg);

/*
** common.c
*/

bool					parse_args(
							t_philo_conf *philo_args,
							int argc,
							char **argv);

/*
** helper.c
*/

long int				h_atoi_strict_unsigned(char *s);
void					h_putnbr(unsigned long num);
void					h_putchar(char c);
void					h_putstr(char *s);
void					*h_calloc(int count, int size);
t_time					h_time_now(void);

#endif
