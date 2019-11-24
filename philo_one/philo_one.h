/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:11:16 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/24 06:55:48 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE
# define PHILO_ONE

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef enum
{
	STATE_EATING,
	STATE_THINKING,
	STATE_SLEEPING,
	STATE_TOOK_FORK,
	STATE_DEAD
}	t_philo_state;


typedef struct
{
	int				id;
	t_philo_state	state;
	t_bool			alive;
	int				forks[2];
	int				finished_time;
}	t_philo

void print_state_change(int timestamp, t_philo_state state);

#endif
