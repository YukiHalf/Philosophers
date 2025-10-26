/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:26:32 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/26 16:42:51 by sdarius-         ###   ########.fr       */
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

void	cleanup_data(t_data *data)
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
		free(data->threads);
	if (data->philo)
		free(data->philo);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->stop_simulation)
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id,
			action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_usleep(long microseconds, t_data *data)
{
	long	start_time;
	long	current_time;

	start_time = get_time() * 1000;
	while (!check_simultation(data))
	{
		current_time = get_time() * 1000;
		if (current_time - start_time >= microseconds)
			break ;
		usleep(500);
	}
}
