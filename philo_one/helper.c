/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:22:49 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/27 10:43:04 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	h_strlen(char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

long int	h_atou_strict(char *s)
{
	long int	num;

	if (*s < '0' || *s > '9')
		return (-1);
	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num *= 10;
		if (num > UINT_MAX)
			return (-1);
		num += *s - '0';
		if (num > UINT_MAX)
			return (-1);
		s++;
	}
	if (*s != '\0')
		return (-1);
	return (num);
}

void		h_putnbr(unsigned long int num)
{
	if (num > 9)
		h_putnbr(num / 10);
	h_putchar(num % 10 + '0');
}

void		h_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

void		h_putstr(char *s)
{
	write(STDOUT_FILENO, s, h_strlen(s));
}

t_time		h_time_now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
