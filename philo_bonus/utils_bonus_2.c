/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:06:48 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/12 17:51:38 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	data->process = (pid_t *)malloc(data->num_of_philos * sizeof(pid_t));
	return (0);
}
