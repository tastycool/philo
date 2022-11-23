/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:33:30 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/23 11:10:51 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_real_time(long time)
{
	return (get_time() - time);
}

void	wait_eat(t_philo *philo)
{
	philo->time_eat = get_time();
	while (1)
	{
		if ((get_time() - philo->time_eat) >= philo->rules->time_to_eat)
			break ;
		usleep(50);
	}
	//printf("time after eat = %lu\n", get_time() - philo->time_eat);
	philo->time_eat = get_time();
}

void	wait_sleep(t_philo *philo)
{
	philo->time_sleep = get_time();
	while (1)
	{
		if ((get_time() - philo->time_sleep) >= philo->rules->time_to_sleep)
			break ;
		usleep(50);
	}
	// printf("time after sleep = %lu\n", get_time() - philo->time_sleep);
	philo->time_sleep = get_time();
}

