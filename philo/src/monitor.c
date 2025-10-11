/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:34:36 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/11 16:40:58 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_rounds(t_data *data, int finished_count)
{
	if (data->number_of_rounds != -1 && finished_count >= data->number_of_philo)
	{
		data->stop_simulation = 1;
	}
}

int	check_died(t_data *data, int i, long time_since_meal)
{
	if (time_since_meal > data->time_to_die)
	{
		print_action(&data->philo[i], "died");
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

int	check_philosophers(t_data *data, int i, int *finished_count)
{
	long	time_since_meal;

	pthread_mutex_lock(&data->death_mutex);
	time_since_meal = get_time() - data->philo[i].last_meal_time;
	if (check_died(data, i, time_since_meal))
		return (1);
	if (data->number_of_rounds != -1
		&& data->philo[i].meals_eaten >= data->number_of_rounds)
		(*finished_count)++;
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		finished_count;

	data = (t_data *)arg;
	while (!data->stop_simulation)
	{
		finished_count = 0;
		i = -1;
		while (++i < data->number_of_philo)
		{
			if (check_philosophers(data, i, &finished_count))
				return (NULL);
		}
		check_rounds(data, finished_count);
		usleep(1000);
	}
	return (NULL);
}
