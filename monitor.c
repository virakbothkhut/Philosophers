/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:33:31 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/01 18:02:19 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_sim *sim, t_actor *a, long now)
{
	long	last_meal;
	long	since_meal;

	pthread_mutex_lock(&a->philo_mutex);
	if (a->is_full)
	{
		pthread_mutex_unlock(&a->philo_mutex);
		return (0);
	}
	last_meal = a->last_meal;
	pthread_mutex_unlock(&a->philo_mutex);
	since_meal = now - last_meal;
	pthread_mutex_lock(&sim->death_check);
	if (!sim->someone_died && since_meal > sim->die_time)
	{
		pthread_mutex_unlock(&sim->death_check);
		return (1);
	}
	pthread_mutex_unlock(&sim->death_check);
	return (0);
}

static void	announce_death(t_sim *sim, t_actor *a, long now)
{
	long	rel_now;

	rel_now = now - sim->start_time;
	pthread_mutex_lock(&sim->print_lock);
	printf("%ld %d died\n", rel_now, a->id);
	pthread_mutex_unlock(&sim->print_lock);
	pthread_mutex_lock(&sim->death_check);
	sim->someone_died = 1;
	pthread_mutex_unlock(&sim->death_check);
}

static int	check_all_philos(t_sim *sim)
{
	int		i;
	long	now;
	int		full_count;

	full_count = 0;
	now = get_time();
	i = 0;
	while (i < sim->total_actors)
	{
		if (check_philo_death(sim, &sim->actors[i], now))
		{
			announce_death(sim, &sim->actors[i], now);
			return (-1);
		}
		pthread_mutex_lock(&sim->actors[i].philo_mutex);
		if (sim->actors[i].is_full)
			full_count++;
		pthread_mutex_unlock(&sim->actors[i].philo_mutex);
		i++;
	}
	return (full_count);
}

void	*monitor_death(void *arg)
{
	t_sim	*sim;
	int		full_count;

	sim = (t_sim *)arg;
	while (1)
	{
		full_count = check_all_philos(sim);
		if (full_count == -1)
			return (NULL);
		if (sim->required_meals != -1
			&& full_count == sim->total_actors)
		{
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
