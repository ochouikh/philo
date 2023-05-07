#include "philo.h"

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		right_fork;
	int		left_fork;

	philo = (t_philo *)arg;
	data = philo->data;
	right_fork = philo->philo_number - 1;
	if (philo->philo_number == data->num_of_philos)
		left_fork = 0;
	else
		left_fork = philo->philo_number;
	while (1)
	{
		pthread_mutex_lock(&data->fork[right_fork]);
		printf("%lld %d has taken a fork\n", current_time() - data->first_time, philo->philo_number);
		pthread_mutex_lock(&data->fork[left_fork]);
		printf("%lld %d has taken a fork\n", current_time() - data->first_time, philo->philo_number);

		printf("%lld %d is eating\n", current_time() - data->first_time, philo->philo_number);
		usleep(data->time_to_eat * 1000);

		pthread_mutex_lock(&philo->mutex_last_meal);
		philo->last_meal = current_time();
		pthread_mutex_unlock(&philo->mutex_last_meal);

		pthread_mutex_lock(&philo->mutex_times_to_eat);
		if (data->five_arg)
			philo->times_to_eat++;
		pthread_mutex_unlock(&philo->mutex_times_to_eat);

		pthread_mutex_unlock(&data->fork[right_fork]);
		pthread_mutex_unlock(&data->fork[left_fork]);

		printf("%lld %d is sleeping\n", current_time() - data->first_time, philo->philo_number);
		usleep(data->time_to_sleep * 1000);

		printf("%lld %d is thinking\n", current_time() - data->first_time, philo->philo_number);
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
		if (data.num_of_philos < 0)
		{
			write(2, "invalid arguments\n", ft_strlen("invalid arguments\n"));
			exit(1);
		}
		data.time_to_die = ft_atoi(argv[2]);
		if (data.time_to_die  < 0)
		{
			write(2, "invalid arguments\n", ft_strlen("invalid arguments\n"));
			exit(1);
		}
		data.time_to_eat = ft_atoi(argv[3]);
		if (data.time_to_eat < 0)
		{
			write(2, "invalid arguments\n", ft_strlen("invalid arguments\n"));
			exit(1);
		}
		data.time_to_sleep = ft_atoi(argv[4]);
		if (data.time_to_sleep < 0)
		{
			write(2, "invalid arguments\n", ft_strlen("invalid arguments\n"));
			exit(1);
		}
		data.first_time = current_time();
		data.philos = (t_philo *)malloc(data.num_of_philos * sizeof(t_philo));
		data.t = (pthread_t *)malloc(data.num_of_philos * sizeof(pthread_t));
		data.fork = (pthread_mutex_t *)malloc(data.num_of_philos * sizeof(pthread_mutex_t));
		if (argv[5])
		{
			data.five_arg = 1;
			data.number_of_times_to_eat = ft_atoi(argv[5]);
		}
		else
			data.five_arg = 0;
		i = 0;
		while (i < data.num_of_philos)
		{
			pthread_mutex_init(&data.fork[i], NULL);
			i++;
		}
		i = 0;
		while (i < data.num_of_philos)
		{
			usleep(100);
			pthread_mutex_init(&data.philos[i].mutex_last_meal, NULL);
			pthread_mutex_init(&data.philos[i].mutex_times_to_eat, NULL);
			data.philos[i].times_to_eat = 0;
			data.philos[i].philo_number = i + 1;
			data.philos[i].last_meal = current_time();
			data.philos[i].data = &data;
			pthread_create(&data.t[i], NULL, &routine, &data.philos[i]);
			i++;
		}
		while (1)
		{
			usleep(100);
			i = 0;
			while(i < data.num_of_philos)
			{
				pthread_mutex_lock(&data.philos[i].mutex_last_meal);
				if (current_time() - data.philos[i].last_meal >= data.time_to_die)
				{
					pthread_mutex_unlock(&data.philos[i].mutex_last_meal);
					printf("%lld %d died\n", current_time() - data.first_time, data.philos[i].philo_number);
					exit(1);
				}
				pthread_mutex_unlock(&data.philos[i].mutex_last_meal);
				
				if (data.five_arg)
				{
					pthread_mutex_lock(&data.philos[i].mutex_times_to_eat);
					if (data.philos[i].times_to_eat == data.number_of_times_to_eat)
					{
						pthread_mutex_unlock(&data.philos[i].mutex_times_to_eat);
						exit(1);
					}
					pthread_mutex_unlock(&data.philos[i].mutex_times_to_eat);
				}
				i++;
			}
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
