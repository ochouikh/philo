#include "philo.h"

void	*routine(void *philo)
{
	t_philos	*data;

	data = (t_philos *)philo;
	pthread_mutex_lock(&data->fork);
	printf("timestamp_in_ms X has taken a fork");
	pthread_mutex_unlock(&data->fork);
	printf("hii\n");
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philos	data;
	int			i;

	if (argc == 5 || argc == 6)
	{
		data.num_of_philos = ft_atoi(argv[1]);
		data.time_to_die = ft_atoi(argv[2]);
		data.time_to_eat = ft_atoi(argv[3]);
		data.time_to_sleep = ft_atoi(argv[4]);
		pthread_mutex_init(&data.fork, NULL);
		if (argv[5])
			data.number_of_times_to_eat = ft_atoi(argv[5]);
		data.t = (pthread_t *)malloc(data.num_of_philos * sizeof(pthread_t));
		i = 0;
		while (i < data.num_of_philos)
		{
			data.t[i] = NULL;
			pthread_create(&data.t[i], NULL, &routine, &data);
			i++;
		}
		i = 0;
		while (i < data.num_of_philos)
		{
			pthread_join(&data.t[i], NULL);
			i++;
		}
	}
	return (0);
}
