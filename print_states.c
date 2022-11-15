/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:09:33 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/15 10:11:54 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->rules->write);
	// printf("philo.time.time = %ld\n", philo->time.time);
	printf("%ld %03d %s", get_real_time(philo->rules->time), philo->philo_id, msg);
	pthread_mutex_unlock(&philo->rules->write);
}