/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:38:28 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/23 11:27:53 by tberube-         ###   ########.fr       */
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
	{
		state_message(philo, MESSAGE_FORK);
		wait_eat(philo);
		philo->rules->dead = 1;
		return (0);
	}
	while (1)
	{
		eat(philo);
		think(philo);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->fork[philo->left_fork]);
	state_message(philo, MESSAGE_FORK);
	pthread_mutex_lock(&philo->rules->fork[philo->right_fork]);
	state_message(philo, MESSAGE_FORK);
	state_message(philo, MESSAGE_EAT);
	wait_eat(philo);
	philo->meals++;
	pthread_mutex_unlock(&philo->rules->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->rules->fork[philo->right_fork]);
	ft_sleep(philo);
}

void	ft_sleep(t_philo *philo)
{
	state_message(philo, MESSAGE_SLEEP);
	wait_sleep(philo);
}

void	think(t_philo *philo)
{
	state_message(philo, MESSAGE_THINK);
}

int	ft_is_dead(t_philo *philo)
{
	if (philo->is_dead == 1)
	{
		philo->rules->dead = 1;
	}
	return (philo->rules->dead);
}
