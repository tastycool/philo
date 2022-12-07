/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boucle_main_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:05:55 by tberube-          #+#    #+#             */
/*   Updated: 2022/12/07 11:34:55 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	boucle_main(t_philo *philo, t_rules *rules)
{
	philo = rules->philo_tab;
	while (rules->i <= rules->nb_philo)
	{
		if (rules->nb_philo == 1)
		{
			one_philo(philo, rules);
			return ;
		}
		pthread_mutex_lock(&rules->stop_time);
		if ((get_time() - philo->time_eat) > \
		philo->rules->time_to_die && philo->time_eat != 0)
		{
			philo_died(philo, rules);
			pthread_mutex_unlock(&rules->stop_time);
			return ;
		}
		pthread_mutex_unlock(&rules->stop_time);
		while (1)
		{	
			pthread_mutex_lock(&rules->stop_meal);
			if (rules->philo_tab[rules->j].meals >= rules->time_must_eat)
			{
				pthread_mutex_unlock(&rules->stop_meal);
				if ((rules->j + 1) == rules->nb_philo)
				{
					philo_full(rules, philo);
					return ;
				}
				rules->j++;
			}
			else
			{
				pthread_mutex_unlock(&rules->stop_meal);
				break ;
			}
		}
		incrementation(rules);
	}
}

void	one_philo(t_philo *philo, t_rules *rules)
{
	state_message(philo, MESSAGE_FORK);
	wait_die(philo);
	printf("%ld %03d %s", get_real_time(rules->time), \
	philo->philo_id, "is dead\n");
}

void	philo_died(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_died);
	philo->rules->dead = 1;
	pthread_mutex_unlock(&rules->stop_died);
	usleep(5000);
	printf("%ld %03d %s", get_real_time(rules->time), \
	philo->philo_id, "is dead\n");
	pthread_mutex_unlock(&philo->philo_dead);
}

void	philo_full(t_rules *rules, t_philo *philo)
{
	(void)philo;
	pthread_mutex_lock(&philo->rules->stop_died);
	rules->philo_full = 1;
	pthread_mutex_unlock(&philo->rules->stop_died);
	usleep(5000);
	printf("all Philo is full\n");
	pthread_mutex_unlock(&philo->philo_dead);
}

void	incrementation(t_rules *rules)
{
	rules->i++;
	rules->j = 0;
	if (rules->i == rules->nb_philo)
		rules->i = 0;
}
