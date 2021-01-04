/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:58:35 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/04 11:52:30 by cacharle         ###   ########.fr       */
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

typedef enum		e_philo_event
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
	t_time			timeout_death;
	t_time			timeout_eat;
	t_time			timeout_sleep;
	long int		meal_num;
}					t_philo_args;

typedef void		*(*t_routine)(void *arg);

/*
** args.c
*/

bool				parse_args(t_philo_args *args, int argc, char **argv);

/*
** helper.c
*/

long int			h_atou_strict(char *s);
t_time				h_time_now(void);
void				h_sleep(t_time sleep_time);

/*
** io.c
*/

void				philo_put(
						size_t id, t_philo_event event, t_time initial_time);
void				philo_put_flush(void);
int					h_err(int ret, const char *format, char *str);

#endif
