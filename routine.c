/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:38:28 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/15 14:16:06 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *philo_data)
{
	t_philo		*philo;
	int			i;
	int			j;

	philo = (t_philo *)philo_data;
	i = 0;
	j = 0;
	if (philo->philo_id % 2 == 0 && j == 0)
	{
		usleep(15000);
		j++;
	}
	if (philo->rules->nb_philo == 1)
	{
		state_message(philo, MESSAGE_FORK);
		usleep(philo->rules->time_to_die);
		philo->is_dead = 1;
	}
	while (ft_is_dead(philo) != 1)
	{
		if (philo->meals <= philo->rules->time_must_eat)
		{
			eat(philo);
			ft_sleep(philo);
		}
		printf("nb_meals = %d\n", philo->meals);
		think(philo);
	}
	printf("dead = %d\n", philo->is_dead);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->fork[philo->rules->philo_tab \
	[philo->rules->philo_tab->philo_id].left_fork]);
	state_message(philo, MESSAGE_FORK);
	pthread_mutex_lock(&philo->rules->fork[philo->rules->philo_tab \
	[philo->rules->philo_tab->philo_id].right_fork]);
	state_message(philo, MESSAGE_FORK);
	state_message(philo, MESSAGE_EAT);
	wait_eat(philo);
	philo->meals++;
	pthread_mutex_unlock(&philo->rules->fork[philo->rules-> \
	philo_tab->philo_id - 1]);
	pthread_mutex_unlock(&philo->rules->fork[philo->rules-> \
	philo_tab->philo_id]);
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
		philo->is_dead = 1;
	}
	return (philo->is_dead);
}
