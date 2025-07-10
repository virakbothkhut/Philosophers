/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:32:53 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/10 00:57:26 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_sim *sim)
{
	int	i;

	i = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->total_actors);
	if (!sim->forks)
	{
		free(sim->actors);
		return (1);
	}
	while (i < sim->total_actors)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->death_check, NULL);
	return (0);
}

static void	assign_forks_and_actor(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->total_actors)
	{
		sim->actors[i].left_fork = &sim->forks[i];
		sim->actors[i].right_fork = &sim->forks[(i +1) % sim->total_actors];
		sim->actors[i].sim = sim;
		sim->actors[i].id = i + 1;
		sim->actors[i].meals_eaten = 0;
		sim->actors[i].is_full = 0;
		sim->actors[i].last_meal = sim->start_time;
		pthread_mutex_init(&sim->actors[i].philo_mutex, NULL);
		i++;
	}
}

static int	parse_args(t_sim *sim, int ac, char **av)
{
	sim->total_actors = ft_atoi(av[1]);
	sim->die_time = ft_atoi(av[2]);
	sim->eat_time = ft_atoi(av[3]);
	sim->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		sim->required_meals = ft_atoi(av[5]);
	else
		sim->required_meals = -1;
	return (0);
}

static int	validate_args(t_sim *sim, int ac)
{
	if (sim->total_actors <= 0 || sim->die_time <= 0
		|| sim->eat_time <= 0 || sim->sleep_time <= 0
		|| (ac == 6 && sim->required_meals <= 0))
	{
		printf("HEYY: inputs must greater than 0\n");
		return (1);
	}
	return (0);
}

int	init_sim(t_sim *sim, int ac, char **av)
{
	if (parse_args(sim, ac, av) != 0)
		return (1);
	if (validate_args(sim, ac) != 0)
		return (1);
	sim->someone_died = 0;
	sim->start_time = get_time();
	sim->actors = malloc(sizeof(t_actor) * sim->total_actors);
	if (!sim->actors)
	{
		printf("Hey: your actor philo failed for allocation\n");
		return (1);
	}
	if (init_mutexes(sim))
	{
		printf("Hey: initialize mutexes is failed\n");
		free(sim->actors);
		return (1);
	}
	assign_forks_and_actor(sim);
	return (0);
}
