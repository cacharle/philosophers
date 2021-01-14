/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:58:26 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/14 10:54:26 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

bool	h_sem_create(const char *name, unsigned int value, sem_t **sem)
{
	if (value == 0)
	{
		*sem = sem_open(name, 0);
		return (*sem != SEM_FAILED);
	}
	else
	{
		sem_unlink(name);
		return ((*sem = sem_open(name,
					O_CREAT | O_EXCL, 0700, value)) != SEM_FAILED);
	}
}
