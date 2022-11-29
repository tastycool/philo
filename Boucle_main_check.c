/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boucle_main_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:05:55 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/29 16:25:31 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo, t_rules *rules)
{
	state_message(philo, MESSAGE_FORK);
	wait_die(philo);
	printf("%ld %03d %s", get_real_time(rules->time), \
	philo->philo_id, "is dead\n");
}

void	philo_died(t_philo *philo, t_rules *rules)
{
	pthread_mutex_unlock(&philo->philo_dead);
	philo->rules->dead = 1;
	//pthread_mutex_lock(&rules->philo_tab->philo_dead);
	//pthread_mutex_lock(&rules->write);
	
	printf("%ld %03d %s", get_real_time(rules->time), \
	philo->philo_id, "is dead\n");
}

void	philo_full(t_rules *rules)
{
	pthread_mutex_unlock(&rules->philo_tab->philo_dead);
	rules->philo_full = 1;
	usleep(500);
	printf("all Philo is full\n");
}

void	incrementation(t_rules *rules)
{
	rules->i++;
	rules->j = 0;
	if (rules->i == rules->nb_philo)
		rules->i = 0;
}