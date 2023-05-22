/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:16:42 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/22 21:19:32 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	initialize_semaphores(t_data *data)
{
	sem_unlink("/forks");
	data->fork = sem_open("/forks", O_CREAT, \
	0666, data->num_of_philos);
	if (data->fork == SEM_FAILED)
		return (printf("sem_open() fail\n"), 1);
	sem_unlink("/print");
	data->sem_print = sem_open("/print", O_CREAT, 0666, 1);
	if (data->sem_print == SEM_FAILED)
		return (printf("sem_open() fail\n"), 1);
	return (0);
}

int	initialize_philo_infos(t_data *data)
{
	int		i;
	char	*num;

	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].philo_number = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal = current_time();
		data->philos[i].times_to_eat = 0;
		num = ft_itoa(i);
		data->philos[i].str_last_meal = ft_strjoin("/last_meal", num);
		sem_unlink(data->philos[i].str_last_meal);
		data->philos[i].sem_last_meal = \
		sem_open(data->philos[i].str_last_meal, O_CREAT, 0666, 1);
		data->philos[i].str_times_to_eat = ft_strjoin("/times_to_eat", num);
		sem_unlink(data->philos[i].str_times_to_eat);
		data->philos[i].sem_times_to_eat = \
		sem_open(data->philos[i].str_times_to_eat, O_CREAT, 0666, 1);
		if ((data->philos[i].sem_times_to_eat == SEM_FAILED)
			|| (data->philos[i].sem_last_meal == SEM_FAILED))
			return (printf("sem_open() fail\n"), 1);
		free(num);
	}
	return (0);
}

void	check_die(t_data *data, int i)
{
	sem_wait(data->philos[i].sem_last_meal);
	if (current_time() - data->philos[i].last_meal >= data->time_to_die)
	{
		sem_post(data->philos[i].sem_last_meal);
		sem_wait(data->sem_print);
		printf("%lld %d died\n", current_time() - data->first_time, \
		data->philos[i].philo_number);
		kill(0, SIGINT);
	}
	sem_post(data->philos[i].sem_last_meal);
}

void	check_times_to_eat(t_data *data, int i)
{
	sem_wait(data->philos[i].sem_times_to_eat);
	if (data->philos[i].times_to_eat >= data->number_of_times_to_eat)
	{
		sem_post(data->philos[i].sem_times_to_eat);
		exit(EXIT_SUCCESS);
	}
	sem_post(data->philos[i].sem_times_to_eat);
}
