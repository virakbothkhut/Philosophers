/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:34:13 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/02 19:34:47 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim	t_sim;
typedef struct s_actor
{
	int					id;
	int					is_full;
	int					meals_eaten;
	long				last_meal;
	pthread_mutex_t		philo_mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_sim				*sim;
}	t_actor;

typedef struct s_sim
{
	int					total_actors;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					required_meals;
	long				start_time;
	int					someone_died;
	int					allowed_philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_check;
	t_actor				*actors;
}	t_sim;

// INIT
int		init_sim(t_sim *sim, int ac, char **av);
int		init_actors(t_sim *sim);

// UTILS
long	get_time(void);
void	safe_print(t_actor *a, char *msg);
int		ft_atoi(const char *str);
int		is_valid_int(char *str);

// ACTION
void	*life_cycle(void *arg);
void	*life_loop(t_actor *a);
void	eat(t_actor *a);
void	think_sleep(t_actor *a);
// void	ft_sleep(long dura_ms);
void	ft_sleep_with_check(long duration, t_sim *s);

// CLEAN
void	cleanup(t_sim *sim);

// START
int		start_simulation(t_sim *sim);

// // Monitor
void	*monitor_death(void *arg);

#endif
