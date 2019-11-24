/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:53:02 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/24 06:35:10 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	if (argc != 5 || argc != 6)
		return (1);
	int philo_nb = ft_atoi(argv[1]);
	int death_timer = ft_atoi(argv[2]);
	int eat_timer = ft_atoi(argv[3]);
	int sleep_timer = ft_atoi(argv[4]);
	if (argc == 6)
		int eat_nb = ft_atoi(argv[5]);
	return (0);
}
