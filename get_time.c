/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:33:30 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/15 12:49:24 by tberube-         ###   ########.fr       */
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
	if (philo->time_eat > philo->rules->time_to_eat)
	{
		philo->is_dead = 1;
		return ;
	}
	while (1)
	{
		if ((get_time() - philo->time_eat) >= philo->rules->time_to_eat)
			break ;
		usleep(50);
	}
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
}

