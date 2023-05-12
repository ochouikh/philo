/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:43:20 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/12 17:50:59 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_data *data, t_philo *philo)
{
	sem_wait(data->fork);
	sem_wait(data->sem_print);
	printf("%lld %d has taken a fork\n", current_time() - data->first_time, \
	philo->philo_number);
	sem_post(data->sem_print);
	sem_wait(data->fork);
	sem_wait(data->sem_print);
	printf("%lld %d has taken a fork\n", current_time() - data->first_time, \
	philo->philo_number);
	sem_post(data->sem_print);
}

void	time_to_eat(t_data *data, t_philo *philo)
{
	sem_wait(data->sem_print);
	printf("%lld %d is eating\n", current_time() - data->first_time, \
	philo->philo_number);
	sem_post(data->sem_print);
	my_usleep(data->time_to_eat);
	sem_wait(philo->sem_last_meal);
	philo->last_meal = current_time();
	sem_post(philo->sem_last_meal);
	sem_wait(philo->sem_last_meal);
	if (data->five_arg)
		philo->times_to_eat++;
	sem_post(philo->sem_last_meal);
	sem_post(data->fork);
	sem_post(data->fork);
}

static void	time_to_sleep_and_think(t_data *data, t_philo *philo)
{
	sem_wait(data->sem_print);
	printf("%lld %d is sleeping\n", current_time() - data->first_time, \
	philo->philo_number);
	sem_post(data->sem_print);
	my_usleep(data->time_to_sleep);
	sem_wait(data->sem_print);
	printf("%lld %d is thinking\n", current_time() - data->first_time, \
	philo->philo_number);
	sem_post(data->sem_print);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		take_forks(data, philo);
		time_to_eat(data, philo);
		time_to_sleep_and_think(data, philo);
	}
	return (NULL);
}
