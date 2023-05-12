/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:43:38 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/12 17:53:30 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philo(t_data *data, int i)
{
	data->process[i] = fork();
	if (data->process[i] == 0)
	{
		usleep(10);
		pthread_create(&data->philos[i].t, NULL, &routine, &data->philos[i]);
		pthread_detach(data->philos[i].t);
		while (1)
		{
			check_die(data, i);
			if (data->five_arg)
				check_times_to_eat(data, i);
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
	if (parse_and_initialize(data, argv))
		return (1);
	initialize_semaphores(data);
	initialize_philo_infos(data);
	i = 0;
	while (i < data->num_of_philos)
	{
		create_philo(data, i);
		i++;
	}
	while (waitpid(0, NULL, 0) != -1);
	return (0);
}
