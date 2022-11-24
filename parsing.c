/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:09:52 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/24 09:22:20 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int ac, char **av, t_rules *rules)
{
	if (ac == 6 || ac == 5)
	{
		check_alpha(ac, av, rules);
		if (rules->error == 1)
			return (1);
		rules->nb_philo = ft_atolong(av[1]);
		rules->time_to_die = ft_atolong(av[2]);
		rules->time_to_eat = ft_atolong(av[3]);
		rules->time_to_sleep = ft_atolong(av[4]);
		if (ac == 6)
			rules->time_must_eat = ft_atolong(av[5]);
		else
			rules->time_must_eat = INT_MAX;
		check_error(rules);
	}
	else
	{
		dprintf(2, "nb argc error\n");
		rules->error = 1;
		return (1);
	}
	if (rules->error == 1)
		return (1);
	return (0);
}

long	ft_atolong(const char *str)
{
	long		retour;
	int			i;
	int			negatif;

	negatif = 1;
	i = 0;
	retour = 0;
	if (str[0] == '-')
	{
		negatif = -1;
		i++;
	}
	while (str[i])
	{
		retour = (str[i] - '0') + (retour * 10);
		i++;
	}
	return (retour * negatif);
}

int	check_error(t_rules *rules)
{
	rules->philo_full = 0;
	rules->philo_tab->is_dead = 0;
	if (rules->nb_philo > 200)
	{
		rules->error = 1;
		dprintf(2, "too many philo\n");
		return (1);
	}
	if (rules->nb_philo <= 0 || rules->time_to_die <= 0 \
	|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0 \
	|| rules->time_must_eat <= 0)
	{
		dprintf(2, "args can't be 0 or negatives\n");
		rules->error = 1;
		return (1);
	}
	return (0);
}

int	check_alpha(int ac, char **av, t_rules *rules)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_strchr(VALIDE_SYMBOL, av[i][j]))
			{
				rules->error = 1;
				dprintf(2, "invalid symbole\n");
				return (1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != '\0')
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *) s);
	return (0);
}
