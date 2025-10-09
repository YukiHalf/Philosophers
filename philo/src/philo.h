/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:21 by sdarius-          #+#    #+#             */
/*   Updated: 2025/10/08 18:01:21 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
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
	t_philo				*philo;
	pthread_t			*threads;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

// Routine & functions related
void					*routine(void *arg);
void					*monitor(void *arg);

void					think(t_philo *philo);

// Helper functions
long					get_time(void);
int						is_num(char c);
void					cleanup_data(t_data *data);
void					print_action(t_philo *philo, char *action);
void					ft_usleep(long microseconds, t_data *data);
void					one_philo(t_data *data);
void					offset_philos(t_philo *philo);
#endif
