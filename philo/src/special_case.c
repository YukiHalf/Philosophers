/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:44:59 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/09 20:21:43 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_data *data)
{
	print_action(data->philo, "has taken a fork");
	ft_usleep(data->time_to_die * 1000, data);
}

void	offset_philos(t_philo *philo)
{
	if (philo->data->number_of_philo % 2 == 1)
	{
		usleep((philo->id - 1) * 20);
	}
	else
	{
		if (philo->id % 2 == 0)
			usleep(70);
	}
}

void 	think(t_philo *philo)
{

	if((get_time() - philo->last_meal_time - philo->data->time_to_eat <= philo->data->time_to_die / 2) && philo->data->number_of_philo % 2 == 1 )
	{
		printf("time %ld\n",get_time()-philo->last_meal_time);
		print_action(philo,"is thinking");
		usleep(philo->data->time_to_eat/2 * 1000);
	}
	else
		print_action(philo,"is thinking");
}
