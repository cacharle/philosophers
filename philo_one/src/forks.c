/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:46:40 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 09:45:46 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t	*forks_new(int num)
{
	int				i;
	pthread_mutex_t	*forks;

	if ((forks = malloc(num * sizeof(pthread_mutex_t))) == NULL)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			forks_destroy(forks, i);
			return (NULL);
		}
	}
	return (forks);
}

void			forks_destroy(pthread_mutex_t *forks, int num)
{
	while (num-- > 0)
		pthread_mutex_destroy(&forks[num]);
	free(forks);
}
