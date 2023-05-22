/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:16:30 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/22 21:24:38 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_number;
	long long		last_meal;
	pthread_mutex_t	mutex_last_meal;
	int				times_to_eat;
	pthread_mutex_t	mutex_times_to_eat;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	pthread_t		*t;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_print;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
	long long		first_time;
	int				five_arg;
	struct s_philo	*philos;
}				t_data;

long		ft_atoi(const char *str);
void		*routine(void *arg);
long long	current_time(void);
void		my_usleep(long long time_to_sleep);
int			parse_and_initialize(t_data *data, char **argv);
int			check_die(t_data *data, int i);
int			check_times_to_eat(t_data *data, int i);
int			check_die_and_eat_times(t_data *data);

#endif
