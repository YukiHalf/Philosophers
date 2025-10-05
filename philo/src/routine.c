/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:11:19 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/05 22:39:21 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(philo_t *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	eat(philo_t *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_usleep(philo->data->time_to_eat * 1000, philo->data);
}

void	sleep_philo(philo_t *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep * 1000, philo->data);
}

void	put_down_forks(philo_t *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	think(philo_t *philo)
{
	print_action(philo, "is thinking");
}

void	*routine(void *arg)
{
	philo_t	*philo;
	data_t	*data;

	philo = (philo_t *)arg;
	data = philo->data;
	if (data->number_of_philo == 1)
	{
		print_action(philo, "has taken a fork");
		ft_usleep(data->time_to_die * 1000, data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(70);
	while (!data->stop_simulation)
	{
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		think(philo);
		if (data->number_of_rounds != -1
			&& philo->meals_eaten >= data->number_of_rounds)
		{
			break ;
		}
	}
	return (NULL);
}
