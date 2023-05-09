#include "philo_bonus.h"

void ft_putstr(char *string)
{
	write(2, string, ft_strlen(string));
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	if (argc == 5 || argc == 6)
	{
		data = malloc(sizeof(t_data));
		data->num_of_philos = ft_atoi(argv[1]);
		if (data->num_of_philos < 0)
		{
			ft_putstr("invalid arguments\n");
			return (1);
		}
		data->time_to_die = ft_atoi(argv[2]);
		if (data->time_to_die  < 0)
		{
			ft_putstr("invalid arguments\n");
			return (1);
		}
		data->time_to_eat = ft_atoi(argv[3]);
		if (data->time_to_eat < 0)
		{
			ft_putstr("invalid arguments\n");
			return (1);
		}
		data->time_to_sleep = ft_atoi(argv[4]);
		if (data->time_to_sleep < 0)
		{
			ft_putstr("invalid arguments\n");
			return (1);
		}
		data->philos = (t_philo *)malloc(data->num_of_philos * sizeof(t_philo));
		data->process = (pid_t *)malloc(data->num_of_philos * sizeof(pid_t));
		data->fork = (sem_t *)malloc(data->num_of_philos * sizeof(sem_t));
		i = 0;
	}
	return (0);
}
