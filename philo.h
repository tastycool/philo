/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:54:02 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/15 14:14:49 by tberube-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define DEBUG printf("debug\n")
# define MESSAGE_EAT "is eating\n"
# define MESSAGE_FORK "has taken a fork\n"
# define MESSAGE_THINK "is thinking\n"
# define MESSAGE_SLEEP "is sleeping\n"
# define MESSAGE_DEAD "is dead\n"
# define VALIDE_SYMBOL "-0123456789"

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
}	t_state;

struct	s_rules;

typedef struct s_philo
{
	int					philo_id;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	int					meals;
	int					is_dead;
	long				time_eat;
	long				time_sleep;
	long				time_think;
	struct s_rules		*rules;
}						t_philo;

typedef struct s_rules
{
	long			time;
	long			real_time;
	int				nb_philo;
	t_philo			philo_tab[200];
	pthread_mutex_t	fork[200];
	int				error;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_must_eat;
	pthread_mutex_t	write;
}					t_rules;

int		check_error(t_rules *rules);
long	ft_atolong(const char *str);
int		parsing(int ac, char **av, t_rules *rules);
int		check_alpha(int ac, char **av, t_rules *rules);
char	*ft_strchr(const char *s, int c);
void	init_philo(t_rules *rules);
time_t	get_time(void);
long	get_real_time(long time);
void	*routine_philo(void *philo);
void	state_message(t_philo *philo, const char *msg);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		ft_is_dead(t_philo *philo);
void	wait_eat(t_philo *philo);
void	wait_sleep(t_philo *philo);
void	boucle_main(t_philo *philo, t_rules *rules);

#endif