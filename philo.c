/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:52:37 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/29 15:15:29 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// 200 philo sa meure
void	boucle_main(t_philo *philo, t_rules *rules)
{
	philo = rules->philo_tab;
	while (rules->i <= rules->nb_philo)
	{
		//pthread_mutex_lock(&rules->philo_tab->philo_dead);
		// pthread_mutex_lock(&rules->write);
		if (rules->nb_philo == 1)
		{
			one_philo(philo, rules);
			return ;
		}
		if ((get_time() - philo->time_eat) > \
		philo->rules->time_to_die && philo->time_eat != 0)
		{
			philo_died(philo, rules);
			return ;
		}
		while (rules->philo_tab[rules->j].meals >= rules->time_must_eat)
		{
			if ((rules->j + 1) == rules->nb_philo)
			{
				philo_full(rules);
				return ;
			}
			rules->j++;
		}
		incrementation(rules);
		//pthread_mutex_unlock(&rules->philo_tab->philo_dead);
		// pthread_mutex_unlock(&rules->write);
	}
}

void	destroy_thread(t_rules *rules)
{
	int	i;

	i = 0;
	while (i <= rules->nb_philo)
	{
		pthread_join(rules->philo_tab[i].thread, NULL);
		i++;
	}
}

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
	init_philo(&rules);
	create_thread(&rules);
	boucle_main(&philo, &rules);
	pthread_mutex_unlock(&rules.write);
	//destroy_thread(&rules);
	return (0);
}