/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:58:35 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/09 03:22:56 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdlib.h>
# include <sys/time.h>

# define FALSE 0
# define TRUE 1

typedef int			t_bool;

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
	int				id;
	t_philo_state	state;
	pthread_t		thread;
}					t_philo;

typedef struct
{
	int				philo_num;
	int 			timeout_death;
	int				timeout_eat;
	int				timeout_sleep;
	int 			meal_num;
}					t_philo_args;

typedef void		(*t_philo_routine)(void *arg);

typedef struct
{
	t_bool			used;
	t_philo			*left;
	t_philo			*right;
}					t_fork;

/*
** common.c
*/

t_bool				parse_args(t_philo_args *philo_args, int argc, char **argv);
void				philo_put_state_change(t_philo *philo, t_philo_event event);

/*
** philo.c
*/

t_philo				*philos_new(int num);
void				philos_destroy(t_philo *philo);

void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

/*
** helper.c
*/

int					h_strtoposint(char *s);
int					h_strlen(char *s);
void				h_putnbr(unsigned long num);
void				h_putchar(char c);
void				h_putstr(char *s);
void				*h_calloc(int count, int size);


#endif
