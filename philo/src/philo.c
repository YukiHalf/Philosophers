/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:01 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/05 19:25:09 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int argc, char **argv, data_t *data)
{
	data->start_time = get_time();
	data->number_of_philo = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->number_of_rounds = atoi(argv[5]);
	else
		data->number_of_rounds = -1;
	data->stop_simulation = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->forks = NULL;
	data->philo = NULL;
	data->threads = NULL;
}

int	allocate_res(data_t *data)
{
	data->philo = malloc(sizeof(philo_t) * data->number_of_philo);
	data->threads = malloc(sizeof(pthread_t) * data->number_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->philo || !data->threads || !data->forks)
	{
		if (data->philo)
			free(data->philo);
		if (data->threads)
			free(data->threads);
		if (data->forks)
			free(data->forks);
		return (0);
	}
	return (1);
}

int	init_philo(data_t *data)
{
	int	i;

	if (!allocate_res(data))
		return (0);
	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1)
			% data->number_of_philo];
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = data->start_time;
		pthread_create(&data->threads[i], NULL, &routine, &data->philo[i]);
		i++;
	}
	return (1);
}

int	valid_args(int argc, char **argv)
{
	int	i;
	int	j;
	int	val;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(is_num(argv[i][j])) || argv[i][j] == '-')
				return (0);
			j++;
		}
		val = atoi(argv[i]);
		if (i == 1 && (val <= 0 || val > 200))
			return (0);
		if (i >= 2 && val <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	data_t	data;
	pthread_t monitor_thread;

	if (argc != 5 && argc != 6)
		return (1);
	if (!valid_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	if (!init_philo(&data))
	{
		printf("Error: Failed to initialize Philosophers\n");
		cleanup_data(&data);
		return (1);
	}
	pthread_create(&monitor_thread,NULL,monitor,&data);
	pthread_join(monitor_thread,NULL);
	cleanup_data(&data);
	printf("Simulation Ended");
	return (0);
}
