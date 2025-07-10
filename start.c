/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:48:35 by vkhut             #+#    #+#             */
/*   Updated: 2025/06/30 16:51:06 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *arg)
{
	t_sim	*sim;
	int		i;
	long	time_since;

	sim = (t_sim *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->total_actors)
		{
			pthread_mutex_lock(&sim->death_check);
			time_since = get_time() - sim->actors[i].last_meal;
			if (time_since > sim->die_time)
			{
				sim->someone_died = 1;
				safe_print(&sim->actors[i], "died");
				pthread_mutex_unlock(&sim->death_check);
				return (NULL);
			}
			pthread_mutex_unlock(&sim->death_check);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
