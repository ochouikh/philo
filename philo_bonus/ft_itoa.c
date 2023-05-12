/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 02:44:39 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/12 15:21:27 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_len(int n)
{
	int	i;

	i = 0;
	while (n % 10 != 0 || i == 0)
	{
		n = n / 10;
		while (n % 10 == 0 && n / 10 != 0)
		{
			n = n / 10;
			i++;
		}
		i++;
	}
	return (i);
}

static char	*ft_swap(char *a, int n)
{
	int		i;
	char	c;

	i = 0;
	while (i < n / 2)
	{
		c = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = c;
		i++;
	}
	return (a);
}

static size_t	ft_is_negative(int n)
{
	if (n == -2147483648)
	{
		n = n + 1;
		n = n * (-1);
		return (n);
	}
	if (n < 0)
		n = n * (-1);
	return (n);
}

static char	*ft_alloc(int n, size_t j)
{
	char	*a;

	if (n < 0)
		a = (char *)malloc((j + 1) * sizeof(char) + 1);
	else
		a = (char *)malloc(j * sizeof(char) + 1);
	return (a);
}

char	*ft_itoa(int n)
{
	char	*a;
	int		i;
	int		j;
	size_t	nb;

	nb = ft_is_negative(n);
	i = ft_len(nb);
	nb = ft_is_negative(n);
	j = i;
	a = ft_alloc(n, j);
	if (a == NULL)
		return (NULL);
	if (n == -2147483648)
		nb = nb + 1;
	i = 0;
	while (i < j || i == 0)
	{
		a[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		a[i++] = '-';
	a = ft_swap(a, i);
	a[i] = '\0';
	return (a);
}
