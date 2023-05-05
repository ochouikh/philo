#include "philo.h"

long long	f(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*routine(void *arg)
{
	t_data				*data;
	t_philo				*philo;
	int					right_fork;
	int					left_fork;

	philo = (t_philo *)arg;
	data = philo->data;
	right_fork = philo->philo_number;
	if (philo->philo_number == data->num_of_philos)
		left_fork = 1;
	else
		left_fork = philo->philo_number + 1;
	while (1)
	{
		pthread_mutex_lock(&data->fork[right_fork]);
		printf("%lld %d has taken a fork\n", f() - data->f, philo->philo_number);
		pthread_mutex_lock(&data->fork[left_fork]);
		printf("%lld %d has taken a fork\n", f() - data->f, philo->philo_number);
		printf("%lld %d is eating\n", f() - data->f, philo->philo_number);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(&data->fork[right_fork]);
		pthread_mutex_unlock(&data->fork[left_fork]);
		printf("%lld %d is sleeping\n", f() - data->f, philo->philo_number);
		usleep(data->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", f() - data->f, philo->philo_number);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (argc == 5 || argc == 6)
	{
		data.num_of_philos = ft_atoi(argv[1]);
		data.philos = (t_philo *)malloc(data.num_of_philos * sizeof(t_philo));
		data.t = (pthread_t *)malloc(data.num_of_philos * sizeof(pthread_t));
		data.fork = (pthread_mutex_t *)malloc(data.num_of_philos * sizeof(pthread_mutex_t));
		data.time_to_die = ft_atoi(argv[2]);
		data.time_to_eat = ft_atoi(argv[3]);
		data.time_to_sleep = ft_atoi(argv[4]);
		data.f = f();
		if (argv[5])
			data.number_of_times_to_eat = ft_atoi(argv[5]);
		i = 0;
		while (i < data.num_of_philos)
		{
			pthread_mutex_init(&data.fork[i], NULL);
			i++;
		}
		i = 0;
		while (i < data.num_of_philos)
		{
			data.philos[i].philo_number = i + 1;
			data.philos[i].data = &data;
			pthread_create(&data.t[i], NULL, &routine, &data.philos[i]);
			i++;
		}
		i = 0;
		while (i < data.num_of_philos)
		{
			pthread_join(data.t[i], NULL);
			i++;
		}
	}
	return (0);
}
