/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:52:37 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/15 14:16:03 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;
	t_rules	rules;
	int		i;

	i = 0;
	parsing(ac, av, &rules);
	if (rules.error == 1)
		return (1);
	rules.time = get_time();
	rules.real_time = get_real_time(rules.time);
	init_philo(&rules);
	while (i < rules.nb_philo)
	{
		if (pthread_create(&(rules.philo_tab[i].thread), NULL, \
		routine_philo, &(rules.philo_tab[i])) != 0)
			printf("Error creating thread\n");
		i++;
	}
	boucle_main(&philo, &rules);
	return (0);
}

void	boucle_main(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	(void)rules;
	while (1)
	{
		i = 0;
		//printf("philo dead = %d\n", philo->is_dead);
		if (philo->is_dead == 1)
		{
			state_message(philo, MESSAGE_DEAD);
			return ;
		}
		//else
			//printf("1\n");
		while (i <= rules->nb_philo)
		{
			//printf("3333333\n");
			if (rules->philo_tab[i].meals == rules->time_must_eat)
				i++;
			else
				break ;
		}
		if (i == rules->nb_philo)
		{
			printf("all Philo is full");
			return ;
		}
		//else
			//printf("2\n");
	}
}