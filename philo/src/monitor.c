/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:34:36 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/05 22:38:00 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_rounds(data_t *data, int finished_count)
{
	if (data->number_of_rounds != -1 && finished_count >= data->number_of_philo)
	{
		data->stop_simulation = 1;
	}
}

void	check_died(data_t *data, int i, long time_since_meal)
{
	if (time_since_meal > data->time_to_die)
	{
		print_action(&data->philo[i], "died");
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->death_mutex);
	}
}

void	*monitor(void *arg)
{
	data_t	*data;
	long	time_since_meal;
	int		i;
	int		finished_count;

	data = (data_t *)arg;
	while (!data->stop_simulation)
	{
		finished_count = 0;
		i = -1;
		while (++i < data->number_of_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			time_since_meal = get_time() - data->philo[i].last_meal_time;
			check_died(data, i, time_since_meal);
			if (data->number_of_rounds != -1
				&& data->philo[i].meals_eaten >= data->number_of_rounds)
				finished_count++;
			pthread_mutex_unlock(&data->death_mutex);
		}
		check_rounds(data, finished_count);
		usleep(1000);
	}
	return (NULL);
}
