/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:54:02 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/14 09:55:41 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define DEBUG printf("debug\n")
# define MESSAGE_EAT "is eating\n"
# define MESSAGE_FORK "as taken a fork\n"
# define MESSAGE_THINK "is thinking\n"
# define MESSAGE_SLEEP "is sleeping\n"

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
}	t_state;

typedef struct s_time
{
	long	time;
	long	real_time;
}			t_time;

struct	s_rules;

typedef struct s_philo
{
	int					philo_id;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	struct s_rules		*rules;
}						t_philo;

typedef struct s_rules
{
	int				nb_philo;
	t_philo			philo_tab[200];
	pthread_mutex_t	fork[200];
	int				error;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_must_eat;
}					t_rules;

int		check_error(t_rules *rules);
long	ft_atolong(const char *str);
int		parsing(int ac, char **av, t_rules *rules);




#endif