/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:58:35 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 08:40:38 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

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
	long int		philo_num;
	t_time 			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	long int		meal_num;
}					t_philo_args;

typedef void		*(*t_routine)(void *arg);

/*
** common.c
*/

bool				parse_args(t_philo_args *args, int argc, char **argv);
void				philo_put(size_t id, t_philo_event event);

/*
** helper.c
*/

long int			h_atou_strict(char *s);
size_t				h_strlen(char *s);
void				h_putnbr(unsigned long num);
void				h_putchar(char c);
void				h_putstr(char *s);
t_time				h_time_now(void);
int					h_err(int ret, const char *format, char *str);

#endif
