/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:22:49 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/30 10:15:14 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

long int	h_atou_strict(char *s)
{
	long int	num;
	char		*origin;

	origin = s;
	if (*s < '0' || *s > '9')
		return (h_err(-1, "Error: %s: is not a number", origin));
	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num *= 10;
		if (num > UINT_MAX)
			return (h_err(-1, "Error: %s: is too big", origin));
		num += *s - '0';
		if (num > UINT_MAX)
			return (h_err(-1, "Error: %s: is too big", origin));
		s++;
	}
	if (*s != '\0')
		return (h_err(-1, "Error: %s: is not a number", origin));
	return (num);
}

t_time		h_time_now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
