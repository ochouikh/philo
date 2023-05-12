/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:57:52 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/12 15:05:01 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg_isaplpha(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_and_initialize(t_data *data, char **argv)
{
	if (check_arg_isaplpha(argv))
		return (printf("numerique arguments required\n"), 1);
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->five_arg = 1;
		data->number_of_times_to_eat = ft_atoi(argv[5]);
	}
	else
		data->five_arg = 0;
	if ((data->num_of_philos <= 0) || (data->time_to_die <= 0)
		|| (data->time_to_eat <= 0) || (data->time_to_sleep <= 0)
		|| (data->five_arg && data->number_of_times_to_eat <= 0))
		return (printf("invalid digits\n"), 1);
	data->first_time = current_time();
	data->philos = (t_philo *)malloc(data->num_of_philos * sizeof(t_philo));
	data->t = (pthread_t *)malloc(data->num_of_philos * sizeof(pthread_t));
	data->fork = (pthread_mutex_t *)malloc(data->num_of_philos * \
	sizeof(pthread_mutex_t));
	return (0);
}

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(long long time_to_sleep)
{
	long long	start;

	start = current_time();
	while (current_time() - start < time_to_sleep)
		usleep(10);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	signe;
	int	i;

	result = 0;
	signe = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
		signe *= -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * signe);
}
