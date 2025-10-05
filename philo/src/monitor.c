/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:34:36 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/05 19:37:20 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	data_t	*data;
	long	time_since_meal;
	int		i;

	data = (data_t *)arg;
	while (!data->stop_simulation)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			time_since_meal = get_time() - data->philo[i].last_meal_time;
			if (time_since_meal > data->time_to_die)
			{
				print_action(&data->philo[i], "died");
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}
		if (data->number_of_rounds != -1
			&& data->philo->meals_eaten >= data->number_of_rounds)
		{
			data->stop_simulation = 1;
			print_action(&data->philo[0], "ROUND HAS ENDED"); // this is for debug
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
