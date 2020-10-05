/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 10:03:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/10/05 14:27:13 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

size_t		st_strlen(char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

static char	*st_nbrcpy(char *dst, long long int num)
{
	if (num > 9)
		dst = st_nbrcpy(dst, num / 10);
	dst[0] = num % 10 + '0';
	dst[1] = '\0';
	return (dst + 1);
}

static void	st_strcat(char *dst, char *str)
{
	while (*dst != '\0')
		dst++;
	while (*str != '\0')
		*dst++ = *str++;
	*dst = '\0';
}

void		philo_put(size_t id, t_philo_event event)
{
	static char	buf[2048];

	buf[0] = '\0';
	st_nbrcpy(buf, h_time_now());
	st_strcat(buf, " ");
	st_nbrcpy(buf + st_strlen(buf), id);
	if (event == EVENT_FORK)
		st_strcat(buf, " has taken fork\n");
	else if (event == EVENT_EAT)
		st_strcat(buf, " is eating\n");
	else if (event == EVENT_SLEEP)
		st_strcat(buf, " is sleeping\n");
	else if (event == EVENT_THINK)
		st_strcat(buf, " is thinking\n");
	else if (event == EVENT_DIE)
		st_strcat(buf, " died\n");
	write(STDOUT_FILENO, buf, st_strlen(buf));
}

int			h_err(int ret, const char *format, char *str)
{
	while (*format != '\0')
	{
		if (format[0] == '%' && format[1] == 's')
		{
			if (str != NULL)
				write(STDERR_FILENO, str, st_strlen(str));
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
