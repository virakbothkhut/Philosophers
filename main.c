/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:33:05 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/02 14:19:47 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	validate_inputs(int ac, char **av)
{
	int		i;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo n t_die t_eat t_sleep [meals]\n");
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_valid_int(av[i]))
		{
			printf("Error input!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_sim	sim;

	if (!validate_inputs(ac, av))
		return (1);
	if (init_sim(&sim, ac, av) != 0)
		return (1);
	if (init_actors(&sim))
		return (1);
	if (start_simulation(&sim))
		return (1);
	cleanup(&sim);
	return (0);
}
