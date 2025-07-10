/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:48:58 by vkhut             #+#    #+#             */
/*   Updated: 2025/07/02 19:27:17 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	safe_print(t_actor *a, char *msg)
{
	pthread_mutex_lock(&a->sim->print_lock);
	pthread_mutex_lock(&a->sim->death_check);
	if (!a->sim->someone_died)
	{
		pthread_mutex_unlock(&a->sim->death_check);
		printf("%ld %d %s\n", get_time() - a->sim->start_time, a->id, msg);
		fflush(stdout);
	}
	else
	{
		pthread_mutex_unlock(&a->sim->death_check);
	}
	pthread_mutex_unlock(&a->sim->print_lock);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

int	is_valid_int(char *str)
{
	int				i;
	unsigned long	num;

	num = 0;
	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if (num > 2147483647)
			return (0);
		i++;
	}
	return (1);
}
