/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:57:44 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/12 15:07:26 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_mutexs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex_print, NULL);
}

void	initialize_and_create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		usleep(10);
		data->philos[i].times_to_eat = 0;
		data->philos[i].philo_number = i + 1;
		data->philos[i].last_meal = current_time();
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].mutex_times_to_eat, NULL);
		pthread_mutex_init(&data->philos[i].mutex_last_meal, NULL);
		pthread_create(&data->t[i], NULL, &routine, &data->philos[i]);
		pthread_detach(data->t[i]);
		i++;
	}
}

int	check_die(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].mutex_last_meal);
	if (current_time() - data->philos[i].last_meal >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
		pthread_mutex_lock(&data->mutex_print);
		printf("%lld %d died\n", current_time() - data->first_time, \
		data->philos[i].philo_number);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
	return (0);
}

int	check_times_to_eat(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].mutex_times_to_eat);
	if (data->philos[i].times_to_eat == data->number_of_times_to_eat)
	{
		pthread_mutex_unlock(&data->philos[i].mutex_times_to_eat);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].mutex_times_to_eat);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("invalid arguments\n"), 1);
	data = (t_data *)malloc(sizeof(t_data));
	if (parse_and_initialize(data, argv))
		return (1);
	initialize_mutexs(data);
	initialize_and_create_philo(data);
	while (1)
	{
		usleep(10);
		i = -1;
		while (++i < data->num_of_philos)
		{
			if (check_die(data, i))
				return (1);
			if (data->five_arg)
				if (check_times_to_eat(data, i))
					return (0);
		}
	}
	return (0);
}
