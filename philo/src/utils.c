/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:05:25 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/26 16:42:30 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simultation(t_data *data)
{
	int	ok;

	ok = 0;
	pthread_mutex_lock(&data->death_mutex);
	if (data->stop_simulation == 1)
		ok = 1;
	pthread_mutex_unlock(&data->death_mutex);
	if (ok == 1)
		return (1);
	return (0);
}
