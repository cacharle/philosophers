/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:22:49 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/14 21:07:54 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

long int			h_strtoposint(char *s)
{
	long int	num;

	if (*s < '0' || *s > '9')
		return (-1);
	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num *= 10;
		num += *s - '0';
		s++;
	}
	if (*s != '\0')
		return (-1);
	return num;
}

int					h_strlen(char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

void				h_putnbr(unsigned long int num)
{
	if (num > 9)
		h_putnbr(num / 10);
	h_putchar(num % 10 + '0');
}

void				h_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

void				h_putstr(char *s)
{
	write(STDOUT_FILENO, s, h_strlen(s));
}

void				*h_calloc(int count, int size)
{
	int		i;
	void	*ptr;

	if ((ptr = malloc(count * size)) == NULL)
		return (NULL);
	i = count * size;
	while (i-- > 0)
		((unsigned char*)ptr)[i] = 0x0;
	return (ptr);
}

t_time				h_timeval_to_time(struct timeval *tp)
{
	t_time	t;

	t = tp->tv_sec * 1000 + tp->tv_usec / 1000;
	return (t);
}

t_time				h_time_now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (h_timeval_to_time(&tv));
}
