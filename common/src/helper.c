/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:22:49 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 11:10:45 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
** No need to check error of gettimeofday
** (only for settimeofday and passed pointer validity)
*/

t_time		h_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
** usleep is not precise and adds delay if we do one big usleep
*/

void		h_sleep(t_time sleep_time)
{
	t_time	start;

	start = h_time_now();
	while (h_time_now() - start < sleep_time)
		usleep(500);
}
