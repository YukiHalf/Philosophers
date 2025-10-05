/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:26:32 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/05 19:01:57 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_num(char c)
{
	return ((c >= '0' && c <= '9'));
}

void	cleanup_data(data_t *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->number_of_philo)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->threads)
	{
		i = -1;
		while (++i < data->number_of_philo)
			pthread_join(data->threads[i], NULL);
		free(data->threads);
	}
	if (data->philo)
		free(data->philo);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

void	print_action(philo_t *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
