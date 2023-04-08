/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:28:46 by afanti            #+#    #+#             */
/*   Updated: 2023/04/07 17:02:41 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(long long nbr, t_philo *data)
{
	long long	n;

	n = get_time() - nbr;
	if (n > data->data->time_to_dead)
	{
		print_message("died", data);
		return (1);
	}
	return (0);
}

void	initialize_philos(t_data *data, int d, int nbr)
{
	d = 0;
	while (nbr > d)
	{
		pthread_mutex_init(&data->forks[d], NULL);
		data->philos[d].eat_nbr = 0;
		d++;
	}
	d = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->sl, NULL);
	while (nbr > d)
	{
		data->philos[d].id = d;
		data->philos[d].data = data;
		data->philos[d].right_fork = d;
		if (d == (nbr - 1))
			data->philos[d].left_fork = (0);
		else
			data->philos[d].left_fork = (d + 1);
		data->philos[d].last_eat = get_time();
		pthread_create(&data->philos[d].thread, NULL,
			&function, &data->philos[d]);
		usleep(100);
		d++;
	}
}

int	check_die_nbr_eat(t_data *data, int d, int nbr)
{
	int	g;
	int	f;

	while (1)
	{
		d = 0;
		g = 0;
		while (nbr > d)
		{
			pthread_mutex_lock(&data->sl);
			f = check_die(data->philos[d].last_eat, &data->philos[d]);
			if (data->philos[d].eat_nbr >= data->nbr_philo_eat
				&& data->nbr_philo_eat > 0)
				g++;
			pthread_mutex_unlock(&data->sl);
			if (f == 1)
				return (1);
			if (g == nbr && nbr != 1)
			{
				pthread_mutex_lock(&data->print);
				return (0);
			}
			d++;
		}
	}
}

int	main_next(t_data *data, int nbr)
{
	int	d;

	data->philos = malloc(sizeof(t_philo) * nbr);
	data->forks = malloc(sizeof(pthread_mutex_t) * nbr);
	data->first_time = get_time();
	d = 0;
	initialize_philos(data, d, nbr);
	check_die_nbr_eat(data, d, nbr);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		nbr;
	int		s;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		s = check_av(av);
		if (s == 0)
			return (print_error("check your input, there is Error"), 1);
		initialization(av, data);
		nbr = ft_atoi(av[1]);
		if (nbr == 0)
			return (print_error("check your input, there is Error"), 1);
		if (ac == 6 && data->nbr_philo_eat == 0)
			return (0);
		main_next(data, nbr);
	}
	else
		print_error("check your arguments");
	return (0);
}
