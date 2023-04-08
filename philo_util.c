/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:24:05 by afanti            #+#    #+#             */
/*   Updated: 2023/04/07 17:51:17 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lld ms \t%d\t %s\n", get_time() - philo->data
		->first_time, philo->id + 1, str);
	if (comp("died", str) != 0)
		pthread_mutex_unlock(&philo->data->print);
}

void	to_sleep(long time)
{
	long	var;

	var = get_time();
	while (get_time() - var < time)
	{
		usleep(200);
	}
}

void	*function(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_message("Has Taken a fork", philo);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_message("Has Taken a fork", philo);
		print_message("is Eating", philo);
		pthread_mutex_lock(&philo->data->sl);
		philo->eat_nbr++;
		pthread_mutex_unlock(&philo->data->sl);
		to_sleep(philo->data->time_to_eat);
		pthread_mutex_lock(&philo->data->sl);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->data->sl);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		print_message("is sleeping", philo);
		to_sleep(philo->data->time_to_sleep);
		print_message("is thinking", philo);
	}
}

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (2, &str[i], 1);
		i++;
	}
}

void	initialization(char **av, t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)data;
	while (av[i])
		i++;
	data->philo_nbr = ft_atoi(av[1]);
	data->time_to_dead = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (i == 6)
		data->nbr_philo_eat = (long)ft_atoi(av[5]);
	else if (i == 5)
		data->nbr_philo_eat = -1;
}
