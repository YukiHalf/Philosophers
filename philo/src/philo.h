/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:21 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/05 22:39:23 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philo_s	philo_t;

typedef struct data_s
{
	int					number_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	int					number_of_rounds;
	int					stop_simulation;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*forks;
	philo_t				*philo;
	pthread_t			*threads;
}						data_t;

typedef struct philo_s
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	data_t				*data;
}						philo_t;

// Routine & functions related
void					*routine(void *arg);
void					*monitor(void *arg);

// Helper functions
long					get_time(void);
int						is_num(char c);
void					cleanup_data(data_t *data);
void					print_action(philo_t *philo, char *action);
void					ft_usleep(long microseconds, data_t *data);
#endif
