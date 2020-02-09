/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:58:35 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/09 23:56:48 by cacharle         ###   ########.fr       */
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
	int 			timeout_death;
	int				timeout_eat;
	int				timeout_sleep;
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

void				philo_eat(int id, int timeout);
void				philo_sleep(int id, int timeout);
void				philo_think(int id);
void				philo_die(int id);

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
