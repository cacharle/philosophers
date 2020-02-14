/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:12:55 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 01:32:37 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_bool				parse_args(t_philo_args *philo_args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (FALSE);
	if ((philo_args->philo_num = h_strtoposint(argv[1])) == -1 ||
		(philo_args->timeout_death = h_strtoposint(argv[2])) == -1 ||
		(philo_args->timeout_eat = h_strtoposint(argv[3])) == -1 ||
		(philo_args->timeout_sleep = h_strtoposint(argv[4])) == -1)
		return (FALSE);
	if (argc == 6)
	{
		if ((philo_args->meal_num = h_strtoposint(argv[5])) == -1)
			return (FALSE);
	}
	else
		philo_args->meal_num = -1;
	return (TRUE);
}

void				philo_put_state_change(int id, t_philo_event event)  // not correct for philo3
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return ;
	h_putnbr(tv.tv_sec);
	h_putnbr(tv.tv_usec / 1000);
	h_putchar(' ');
	h_putnbr(id);
	if (event == EVENT_FORK)
		h_putstr(" has taken fork\n");
	else if (event == EVENT_EATING)
		h_putstr(" is eating\n");
	else if (event == EVENT_SLEEPING)
		h_putstr(" is sleeping\n");
	else if (event == EVENT_THINKING)
		h_putstr(" is thinking\n");
	else if (event == EVENT_DIED)
		h_putstr(" died\n");
}
