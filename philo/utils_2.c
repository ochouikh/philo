/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:33:16 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/22 20:39:46 by ochouikh         ###   ########.fr       */
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

static void	initialize(t_data *data, char **argv)
{
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
	data->first_time = current_time();
}

int	parse_and_initialize(t_data *data, char **argv)
{
	if (check_arg_isaplpha(argv))
		return (printf("numerique arguments required\n"), 1);
	initialize(data, argv);
	if ((data->num_of_philos <= 0) || (data->time_to_die <= 0)
		|| (data->time_to_eat <= 0) || (data->time_to_sleep <= 0)
		|| (data->five_arg && data->number_of_times_to_eat <= 0))
		return (printf("invalid digits\n"), 1);
	data->philos = (t_philo *)malloc(data->num_of_philos * sizeof(t_philo));
	if (!data->philos)
		return (printf("malloc() fail\n"), 1);
	data->t = (pthread_t *)malloc(data->num_of_philos * sizeof(pthread_t));
	if (!data->t)
		return (printf("malloc() fail\n"), 1);
	data->fork = (pthread_mutex_t *)malloc(data->num_of_philos * \
	sizeof(pthread_mutex_t));
	if (!data->fork)
		return (printf("malloc() fail\n"), 1);
	return (0);
}
