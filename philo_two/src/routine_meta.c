/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_meta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:31:54 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 13:32:38 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*routine_flush(t_philo_conf *conf)
{
	while (true)
	{
		sem_wait(conf->sem_stdout);
		philo_put_flush();
		sem_post(conf->sem_stdout);
		usleep(250000);
	}
}

void	*routine_meal_num(t_philo_conf *conf)
{
	long int	i;

	if (conf->meal_num == -1)
		return (NULL);
	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_meal_num);
	i = -1;
	while (++i < conf->philo_num)
		sem_wait(conf->sem_meal_num);
	sem_wait(conf->sem_stdout);
	sem_post(conf->sem_finish);
	return (NULL);
}
