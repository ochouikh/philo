/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:57:50 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/15 16:26:35 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die_and_eat_times(t_data *data)
{
	int		i;
	int		j;

	while (1)
	{
		j = 0;
		i = -1;
		while (++i < data->num_of_philos)
		{
			usleep(10);
			if (check_die(data, i))
				return (1);
			if (data->five_arg && check_times_to_eat(data, i))
				j++;
		}
		if (j == data->num_of_philos)
			break ;
		usleep(900);
	}
	return (0);
}

static void	take_forks(t_data *data, t_philo *philo, int right, int left)
{
	pthread_mutex_lock(&data->fork[right]);
	pthread_mutex_lock(&data->mutex_print);
	printf("%lld %d has taken a fork\n", current_time() - data->first_time, \
	philo->philo_number);
	pthread_mutex_unlock(&data->mutex_print);
	pthread_mutex_lock(&data->fork[left]);
	pthread_mutex_lock(&data->mutex_print);
	printf("%lld %d has taken a fork\n", current_time() - data->first_time, \
	philo->philo_number);
	pthread_mutex_unlock(&data->mutex_print);
}

static void	time_to_eat(t_data *data, t_philo *philo, int right, int left)
{
	pthread_mutex_lock(&data->mutex_print);
	printf("%lld %d is eating\n", current_time() - data->first_time, \
	philo->philo_number);
	pthread_mutex_unlock(&data->mutex_print);
	my_usleep(data->time_to_eat);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_lock(&philo->mutex_times_to_eat);
	if (data->five_arg)
		philo->times_to_eat++;
	pthread_mutex_unlock(&philo->mutex_times_to_eat);
	pthread_mutex_unlock(&data->fork[right]);
	pthread_mutex_unlock(&data->fork[left]);
}

static void	time_to_sleep_and_think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mutex_print);
	printf("%lld %d is sleeping\n", current_time() - data->first_time, \
	philo->philo_number);
	pthread_mutex_unlock(&data->mutex_print);
	my_usleep(data->time_to_sleep);
	pthread_mutex_lock(&data->mutex_print);
	printf("%lld %d is thinking\n", current_time() - data->first_time, \
	philo->philo_number);
	pthread_mutex_unlock(&data->mutex_print);
}

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		right;
	int		left;

	philo = (t_philo *)arg;
	data = philo->data;
	right = philo->philo_number - 1;
	if (philo->philo_number == data->num_of_philos)
		left = 0;
	else
		left = philo->philo_number;
	while (1)
	{
		take_forks(data, philo, right, left);
		time_to_eat(data, philo, right, left);
		time_to_sleep_and_think(data, philo);
	}
	return (NULL);
}
