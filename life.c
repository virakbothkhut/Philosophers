/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:33:00 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/01 18:05:36 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_cycle(void *arg)
{
	t_actor	*a;

	a = (t_actor *)arg;
	if (a->id % 2 == 0)
		usleep((a->id % 10) * 1000);
	return (life_loop(a));
}

void	*life_loop(t_actor *a)
{
	while (1)
	{
		pthread_mutex_lock(&a->sim->death_check);
		if (a->sim->someone_died)
		{
			pthread_mutex_unlock(&a->sim->death_check);
			break ;
		}
		pthread_mutex_unlock(&a->sim->death_check);
		eat(a);
		if (a->sim->required_meals != -1
			&& a->meals_eaten >= a->sim->required_meals)
		{
			pthread_mutex_lock(&a->philo_mutex);
			a->is_full = 1;
			pthread_mutex_unlock(&a->philo_mutex);
			break ;
		}
		think_sleep(a);
	}
	return (NULL);
}
