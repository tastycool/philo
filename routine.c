/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:38:28 by tberube-          #+#    #+#             */
/*   Updated: 2022/12/07 11:27:54 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *philo_data)
{
	t_philo		*philo;

	philo = (t_philo *)philo_data;
	if (philo->philo_id % 2 == 0)
		usleep(250);
	if (philo->rules->nb_philo == 1)
		return (0);
	// while (philo->rules->dead == 0 && philo->rules->philo_full == 0)
	while(1)
	{
		pthread_mutex_lock(&philo->rules->stop_died);
		if (philo->rules->dead == 1 || philo->rules->philo_full == 1)
		{
			pthread_mutex_unlock(&philo->rules->stop_died);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->stop_died);
		pthread_mutex_lock(&philo->philo_dead);
		eat(philo);
		pthread_mutex_unlock(&philo->philo_dead);
		think(philo);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->rules->stop_died);
	if (philo->rules->dead == 0 && philo->rules->philo_full == 0)
		state_message(philo, MESSAGE_FORK);
	pthread_mutex_unlock(&philo->rules->stop_died);
	pthread_mutex_lock(&philo->rules->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->rules->stop_died);
	if (philo->rules->dead == 0 && philo->rules->philo_full == 0)
		state_message(philo, MESSAGE_FORK);
	pthread_mutex_unlock(&philo->rules->stop_died);
	pthread_mutex_lock(&philo->rules->stop_died);
	if (philo->rules->dead == 0 && philo->rules->philo_full == 0)
		state_message(philo, MESSAGE_EAT);
	pthread_mutex_unlock(&philo->rules->stop_died);
	wait_eat(philo);
	pthread_mutex_lock(&philo->rules->stop_meal);
	philo->meals++;
	pthread_mutex_unlock(&philo->rules->stop_meal);
	pthread_mutex_unlock(&philo->rules->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->rules->fork[philo->right_fork]);
	ft_sleep(philo);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->stop_died);
	if (philo->rules->dead == 0 && philo->rules->philo_full == 0)
		state_message(philo, MESSAGE_SLEEP);
	pthread_mutex_unlock(&philo->rules->stop_died);
	wait_sleep(philo);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->stop_died);
	if (philo->rules->dead == 0 && philo->rules->philo_full == 0)
		state_message(philo, MESSAGE_THINK);
	pthread_mutex_unlock(&philo->rules->stop_died);
}
