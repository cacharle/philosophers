/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:12:55 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 11:12:26 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int		st_err(int ret, const char *format, char *str)
{
	while (*format != '\0')
	{
		if (format[0] == '%' && format[1] == 's')
		{
			if (str != NULL)
			{
				while (*str != '\0')
					write(STDERR_FILENO, str++, 1);
			}
			format += 2;
		}
		else
		{
			write(STDERR_FILENO, format, 1);
			format++;
		}
	}
	write(STDERR_FILENO, "\n", 1);
	return (ret);
}

static long int	st_atou_strict(char *s)
{
	long int	num;
	char		*origin;

	origin = s;
	if (*s < '0' || *s > '9')
		return (st_err(-1, "Error: %s: is not a number", origin));
	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num *= 10;
		if (num > UINT_MAX)
			return (st_err(-1, "Error: %s: is too big", origin));
		num += *s - '0';
		if (num > UINT_MAX)
			return (st_err(-1, "Error: %s: is too big", origin));
		s++;
	}
	if (*s != '\0')
		return (st_err(-1, "Error: %s: is not a number", origin));
	return (num);
}

bool			parse_args(t_philo_args *args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		return (st_err(false, "Usage: %s philosophers_num deatst_timeout"
			"eat_timeout sleep_timeout [meal_num]", argv[0]));
	}
	if ((args->philo_num = st_atou_strict(argv[1])) == -1
		|| (args->timeout_death = st_atou_strict(argv[2])) == -1
		|| (args->timeout_eat = st_atou_strict(argv[3])) == -1
		|| (args->timeout_sleep = st_atou_strict(argv[4])) == -1)
		return (false);
	if (argc == 6)
	{
		if ((args->meal_num = st_atou_strict(argv[5])) == -1)
			return (false);
	}
	else
		args->meal_num = -1;
	return (true);
}
