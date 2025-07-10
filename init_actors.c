/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_actors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:32:43 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/09 17:54:04 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_actors(t_sim *sim)
{
	int		i;
	t_actor	*a;

	if (!sim->actors)
		return (1);
	i = 0;
	while (i < sim->total_actors)
	{
		a = &sim->actors[i];
		a->id = i + 1;
		a->is_full = 0;
		a->meals_eaten = 0;
		a->last_meal = sim->start_time;
		pthread_mutex_init(&a->philo_mutex, NULL);
		a->left_fork = &sim->forks[i];
		a->right_fork = &sim->forks[(i + 1) % sim->total_actors];
		a->sim = sim;
		i++;
	}
	return (0);
}

void	think_sleep(t_actor *a)
{
	long	last_eat;
	long	think_time;

	pthread_mutex_lock(&a->philo_mutex);
	last_eat = get_time() - a->last_meal;
	pthread_mutex_unlock(&a->philo_mutex);
	think_time = (a->sim->die_time - last_eat - a->sim->eat_time) / 2;
	if (think_time < 0)
		think_time = 0;
	else if (think_time > 200)
		think_time = 200;
	safe_print(a, "is thinking");
	ft_sleep_with_check(think_time, a->sim);
	safe_print(a, "is sleeping");
	ft_sleep_with_check(a->sim->sleep_time, a->sim);
}

void	ft_sleep_with_check(long duration, t_sim *s)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		pthread_mutex_lock(&s->death_check);
		if (s->someone_died)
		{
			pthread_mutex_unlock(&s->death_check);
			break ;
		}
		pthread_mutex_unlock(&s->death_check);
		usleep(500);
	}
}
