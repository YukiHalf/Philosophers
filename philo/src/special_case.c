/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:44:59 by sdarius-          #+#    #+#             */
/*   Updated: 2025/11/14 21:39:05 by sdarius-         ###   ########.fr       */
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

void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
	if (philo->data->number_of_philo % 2 == 0)
	{
		ft_usleep(philo->data->time_to_eat / 10, philo->data);
	}
}

long	ft_atol(char *str)
{
	int		i;
	long	nbr;

	nbr = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+')
		i++;
	while (str[i])
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr);
}

void	message_error(void)
{
	printf("The args you provided don't fit the standard.\n");
}
