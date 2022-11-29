/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:09:33 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/29 16:24:03 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_message(t_philo *philo, const char *msg)
{
	if (philo->rules->dead == 0 && philo->rules->philo_full == 0)
	{
		if (philo->rules->dead == 1 || philo->rules->philo_full == 1)
			pthread_mutex_lock(&philo->philo_dead);
		pthread_mutex_lock(&philo->rules->write);
		printf("%ld %03d %s", get_real_time(philo->rules->time), philo->philo_id, msg);
		pthread_mutex_unlock(&philo->rules->write);
	}
	//DEBUG;
}