/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:16:30 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/04 19:33:41 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philos
{
	pthread_t		*t;
	pthread_mutex_t	fork;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
}				t_philos;

int		ft_atoi(const char *str);

#endif
