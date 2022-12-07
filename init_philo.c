/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:35:57 by tberube-          #+#    #+#             */
/*   Updated: 2022/12/07 09:51:12 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo_tab[i].rules = rules;
		rules->philo_tab[i].philo_id = i + 1;
		rules->philo_tab[i].left_fork = i;
		pthread_mutex_init(&rules->fork[i], NULL);
		pthread_mutex_init(&rules->philo_tab[i].philo_dead, NULL);
		rules->philo_tab[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philo_tab[i].meals = 0;
		rules->philo_tab[i].time_need_to_eat = rules->time_to_eat;
		rules->philo_tab[i].time_need_to_sleep = rules->time_to_sleep;
		i++;
	}
}

int	destroy_thread(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i <= rules->nb_philo)
		pthread_join(rules->philo_tab[i].thread, NULL);
	while (++i <= rules->nb_philo)
	{
		if (pthread_mutex_destroy(&rules->fork[i]) != 0)
		{
			printf("mutex_destroy error\n");
			return (1);
		}
	}
	if (pthread_mutex_destroy(&rules->write) != 0 \
	|| pthread_mutex_destroy(&rules->philo_tab->philo_dead))
	{
		printf("mutex_destroy error\n");
		return (1);
	}
	return (0);
}
