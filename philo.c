/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:52:37 by tberube-          #+#    #+#             */
/*   Updated: 2022/12/07 11:24:10 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(rules->philo_tab[i].thread), NULL, \
		routine_philo, &(rules->philo_tab[i])) != 0)
			printf("Error creating thread\n");
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;
	t_rules	rules;

	rules.i = 0;
	rules.j = 0;
	parsing(ac, av, &rules);
	if (pthread_mutex_init(&rules.write, NULL) != 0)
		rules.error = 1;
	if (rules.error == 1)
		return (1);
	rules.time = get_time();
	rules.real_time = get_real_time(rules.time);
	pthread_mutex_init(&rules.stop_time, NULL);
	pthread_mutex_init(&rules.stop_died, NULL);
	pthread_mutex_init(&rules.stop_meal, NULL);
	init_philo(&rules);
	create_thread(&rules);
	boucle_main(&philo, &rules);
	if (destroy_thread(&rules) != 0)
		return (1);
	return (0);
}
