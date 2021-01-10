/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <me@cacharle.xyz>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 10:03:53 by cacharle          #+#    #+#             */
/*   Updated: 2021/01/10 11:06:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char		*st_nbrcpy(char *dst, long long int num)
{
	if (num > 9)
		dst = st_nbrcpy(dst, num / 10);
	dst[0] = num % 10 + '0';
	return (dst + 1);
}

static char		*st_strcpy_end(char *dst, const char *str)
{
	while (*str != '\0')
		*dst++ = *str++;
	return (dst);
}

#define PHILO_PUT_BUF_SIZE 20000

static char		g_buf[PHILO_PUT_BUF_SIZE + 256] = {'\0'};
static char		*g_curr = g_buf;

void			philo_put(size_t id, t_philo_event event, t_time initial_time)
{
	g_curr = st_nbrcpy(g_curr, h_time_now() - initial_time);
	g_curr = st_strcpy_end(g_curr, " ");
	g_curr = st_nbrcpy(g_curr, id);
	if (event == EVENT_FORK)
		g_curr = st_strcpy_end(g_curr, " has taken fork\n");
	else if (event == EVENT_EAT)
		g_curr = st_strcpy_end(g_curr, " is eating\n");
	else if (event == EVENT_SLEEP)
		g_curr = st_strcpy_end(g_curr, " is sleeping\n");
	else if (event == EVENT_THINK)
		g_curr = st_strcpy_end(g_curr, " is thinking\n");
	else if (event == EVENT_DIE)
		g_curr = st_strcpy_end(g_curr, " died\n");
	if (g_curr - g_buf > PHILO_PUT_BUF_SIZE)
		philo_put_flush();
}

void			philo_put_flush(void)
{
	write(STDOUT_FILENO, g_buf, g_curr - g_buf);
	g_curr = g_buf;
	g_buf[0] = '\0';
}

#define PHILO_SEM_EAT_BUF_SIZE 2048

const char		*philo_sem_eat_name(const char *prefix, long int id)
{
	static char	buf[PHILO_SEM_EAT_BUF_SIZE];
	char		*end;

	buf[0] = '\0';
	end = st_strcpy_end(buf, prefix);
	st_nbrcpy(end, id);
	return (buf);
}
