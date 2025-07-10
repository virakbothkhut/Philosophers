/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:47:43 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/01 18:06:14 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_sim *sim)
{
	pthread_t	monitor;
	int			i;

	sim->start_time = get_time();
	if (pthread_create(&monitor, NULL, monitor_death, sim) != 0)
		return (1);
	i = 0;
	while (i < sim->total_actors)
	{
		if (pthread_create(&sim->actors[i].thread, NULL,
				life_cycle, &sim->actors[i]) != 0)
		{
			usleep(100);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < sim->total_actors)
	{
		pthread_join(sim->actors[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
