/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:31:53 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/10 03:20:52 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

static void	wait_for_death(t_actor *a)
{
	t_sim	*s;

	s = a->sim;
	while (1)
	{
		pthread_mutex_lock(&s->death_check);
		if (s->someone_died)
		{
			pthread_mutex_unlock(&s->death_check);
			pthread_mutex_unlock(a->left_fork);
			return ;
		}
		pthread_mutex_unlock(&s->death_check);
		usleep(1000);
	}
}

static void	left_to_right(t_actor *a)
{
	pthread_mutex_lock(a->left_fork);
	safe_print(a, "has taken a fork");
	if (a->left_fork == a->right_fork)
	{
		pthread_mutex_unlock(a->left_fork);
		wait_for_death(a);
		return ;
	}
	pthread_mutex_lock(a->right_fork);
	safe_print(a, "has taken a fork");
}

static	void	right_to_left(t_actor *a)
{
	pthread_mutex_lock(a->right_fork);
	safe_print(a, "has taken a fork");
	if (a->left_fork == a->right_fork)
	{
		pthread_mutex_unlock(a->right_fork);
		wait_for_death(a);
		return ;
	}
	pthread_mutex_lock(a->left_fork);
	safe_print(a, "has taken a fork");
}

static void	take_forks(t_actor *a)
{
	if (a->id % 2 == 0)
	{
		left_to_right(a);
	}
	else
	{
		right_to_left(a);
	}
}

void	eat(t_actor *a)
{
	t_sim	*s;
	long	now;
	int		died;

	s = a->sim;
	take_forks(a);
	now = get_time();
	pthread_mutex_lock(&a->philo_mutex);
	a->last_meal = now;
	pthread_mutex_unlock(&a->philo_mutex);
	safe_print(a, "is eating");
	ft_sleep_with_check(s->eat_time, s);
	pthread_mutex_lock(&s->death_check);
	died = s->someone_died;
	pthread_mutex_unlock(&s->death_check);
	if (!died)
	{
		pthread_mutex_lock(&a->philo_mutex);
		a->meals_eaten++;
		pthread_mutex_unlock(&a->philo_mutex);
	}
	pthread_mutex_unlock(a->right_fork);
	pthread_mutex_unlock(a->left_fork);
}
