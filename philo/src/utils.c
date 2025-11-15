/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:05:25 by sdarius-          #+#    #+#             */
/*   Updated: 2025/11/15 14:19:27 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simultation(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->stop_mutex);
	status = data->philo[0].stop_simulation;
	pthread_mutex_unlock(&data->stop_mutex);
	return (status);
}

void	set_stop(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->stop_mutex);
	while (++i < data->number_of_philo)
		data->philo[i].stop_simulation = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}
