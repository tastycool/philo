/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:52:37 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/14 09:58:21 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	//t_philo	philo;
	t_rules	rules;
	//t_time	time;

	// rules.philo_tab = &philo;
	//rules
	rules.error = parsing(ac, av, &rules);
	if (rules.error == 1)
		return (1);
	//init_philo();
}