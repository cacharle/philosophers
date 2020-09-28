/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:22:49 by cacharle          #+#    #+#             */
/*   Updated: 2020/09/28 14:54:17 by cacharle         ###   ########.fr       */
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

int			h_err(int ret, const char *format, ...)
{
	char	*str;
	va_list	ap;

	va_start(ap, format);
	while (*format != '\0')
	{
		if (format[0] == '%' && format[1] == 's')
		{
			str = va_arg(ap, char*);
			if (str != NULL)
				write(STDERR_FILENO, str, h_strlen(str));
			format += 2;
		}
		else
		{
			write(STDERR_FILENO, format, 1);
			format++;
		}
	}
	va_end(ap);
	write(STDERR_FILENO, "\n", 1);
	return (ret);
}

t_time		h_time_now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
