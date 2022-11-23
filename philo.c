/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:52:37 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/23 13:30:37 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// 200 philo sa meure

void	boucle_main(t_philo *philo, t_rules *rules)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	philo = rules->philo_tab;
	while (i <= rules->nb_philo)
	{
		if ((get_time() - philo->time_eat) > philo->rules->time_to_die && philo->time_eat != 0)
		{
			philo->rules->dead = 1;
			printf("time last eat = %lu\n", get_time() - philo->time_eat);
			// pthread_mutex_lock(&rules->mort);
			// usleep(1);
			//state_message(philo, MESSAGE_DEAD);
			printf("%ld %03d %s", get_real_time(rules->time), philo->philo_id, "is dead\n");
			return ;
		}
		while (rules->philo_tab[j].meals >= rules->time_must_eat)
		{
			if ((j + 1) == rules->nb_philo)
			{
				pthread_mutex_lock(&philo->rules->write);
				printf("all Philo is full\n");
				return ;
			}
			j++;
		}
		i++;
		j = 0;
		if (i == rules->nb_philo)
			i = 0;
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
	//destroy_thread(&rules);
	return (0);
}