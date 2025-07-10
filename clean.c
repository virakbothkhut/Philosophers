/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:32:39 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/10 03:17:28 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->total_actors)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
	i = 0;
	while (i < sim->total_actors)
	{
		pthread_mutex_destroy(&sim->actors[i].philo_mutex);
		i++;
	}
	free(sim->actors);
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->death_check);
}
