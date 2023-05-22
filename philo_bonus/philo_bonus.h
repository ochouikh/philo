/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:48:53 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/22 21:19:50 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <signal.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo
{
	pthread_t		t;
	int				philo_number;
	long long		last_meal;
	int				times_to_eat;
	char			*str_last_meal;
	sem_t			*sem_last_meal;
	char			*str_times_to_eat;
	sem_t			*sem_times_to_eat;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	pid_t			*process;
	sem_t			*fork;
	sem_t			*sem_print;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
	long long		first_time;
	int				five_arg;
	struct s_philo	*philos;
}				t_data;

long		ft_atoi(const char *str);
long long	current_time(void);
void		my_usleep(long long time_to_sleep);
int			ft_strlen(char *str);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);
int			parse_and_initialize(t_data *data, char **argv);
int			initialize_semaphores(t_data *data);
int			initialize_philo_infos(t_data *data);
void		check_die(t_data *data, int i);
void		check_times_to_eat(t_data *data, int i);
void		*routine(void *arg);

#endif
