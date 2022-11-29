/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberube- <tberube-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:54:02 by tberube-          #+#    #+#             */
/*   Updated: 2022/11/29 15:08:23 by tberube-         ###   ########.fr       */
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
	int					left_fork;
	int					right_fork;
	int					meals;
	int					is_dead;
	pthread_t			thread;
	long				time_eat;
	long				time_sleep;
	long				time_think;
	long				time_die;
	pthread_mutex_t		philo_dead;
	struct s_rules		*rules;
}						t_philo;

typedef struct s_rules
{
	long			time;
	long			real_time;
	int				nb_philo;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	mort;
	int				error;
	int				i;
	int				j;
	int				dead;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_must_eat;
	int				philo_full;
	pthread_mutex_t	write;
	t_philo			philo_tab[200];
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
void	destroy_thread(t_rules *rules);
void	create_thread(t_rules *rules);
void	wait_die(t_philo *philo);
void	one_philo(t_philo *philo, t_rules *rules);
void	philo_died(t_philo *philo, t_rules *rules);
void	incrementation(t_rules *rules);
void	philo_full(t_rules *rules);

#endif