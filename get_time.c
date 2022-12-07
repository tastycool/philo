/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:33:30 by tberube-          #+#    #+#             */
/*   Updated: 2022/12/07 11:20:02 by tberube-         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->rules->stop_time);
	philo->time_eat = get_time();
	pthread_mutex_unlock(&philo->rules->stop_time);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->stop_time);
		if ((get_time() - philo->time_eat) >= philo->time_need_to_eat)
		{
			pthread_mutex_unlock(&philo->rules->stop_time);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->stop_time);
		usleep(50);
	}
}

void	wait_sleep(t_philo *philo)
{
	// pthread_mutex_lock(&philo->rules->stop_time);
	philo->time_sleep = get_time();
	while (1)
	{
		if ((get_time() - philo->time_sleep) >= philo->time_need_to_sleep)
			break ;
		usleep(50);
	}
	// pthread_mutex_unlock(&philo->rules->stop_time);
}

void	wait_die(t_philo *philo)
{
	philo->time_die = get_time();
	while (1)
	{
		if ((get_time() - philo->time_die) >= philo->rules->time_to_die)
			break ;
		usleep(50);
	}
}
