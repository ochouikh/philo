/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:43:38 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/22 21:16:36 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philo(t_data *data, int i)
{
	data->process[i] = fork();
	if (data->process[i] == -1)
	{
		printf("fork() fail\n");
		exit(EXIT_FAILURE);
	}
	if (data->process[i] == 0)
	{
		if (pthread_create(&data->philos[i].t, NULL, &routine, \
		&data->philos[i]) != 0)
			kill(0, SIGINT);
		if (pthread_detach(data->philos[i].t) != 0)
			kill(0, SIGINT);
		while (1)
		{
			check_die(data, i);
			if (data->five_arg)
				check_times_to_eat(data, i);
			usleep(1500);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("invalid arguments\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("malloc() fail\n"), 1);
	if (parse_and_initialize(data, argv))
		return (1);
	if (initialize_semaphores(data))
		return (1);
	if (initialize_philo_infos(data))
		return (1);
	i = 0;
	while (i < data->num_of_philos)
	{
		create_philo(data, i);
		i++;
	}
	while (waitpid(0, NULL, 0) != -1)
		;
	return (0);
}
