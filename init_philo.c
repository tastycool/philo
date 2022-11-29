/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:35:57 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/29 15:10:05 by tberube-         ###   ########.fr       */
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
		i++;
	}
}
