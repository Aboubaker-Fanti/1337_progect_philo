/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_uti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:11:48 by afanti            #+#    #+#             */
/*   Updated: 2023/04/08 11:53:10 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	c;
	int	s;

	i = 0;
	c = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = c * 10 + (str[i] - 48);
		i++;
	}
	return (c * s);
}

long long	get_time(void)
{
	struct timeval	current_ti;

	gettimeofday(&current_ti, NULL);
	return ((current_ti.tv_sec) * 1000 + (current_ti.tv_usec) / 1000);
}

int	comp(char *str, char *st)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] != st[i])
			return (1);
		i++;
	}
	if (str[i] != '\0' || st[i] != '\0')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || (c == 43))
		return (1);
	return (0);
}

int	check_av(char **av)
{
	int	d;
	int	i;
	int	s;

	i = 1;
	s = 0;
	while (av[i])
	{
		s = 0;
		while (av[i][s])
		{
			d = ft_isdigit(av[i][s]);
			if (d == 0)
				return (0);
			s++;
		}
		i++;
	}
	return (1);
}
