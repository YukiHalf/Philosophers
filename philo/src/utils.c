/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:05:25 by sdarius-          #+#    #+#             */
/*   Updated: 2025/11/11 16:47:46 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simultation(t_data *data)
{
	int result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->stop_simulation;
	pthread_mutex_unlock(&data->death_mutex);
	return(result);
}
