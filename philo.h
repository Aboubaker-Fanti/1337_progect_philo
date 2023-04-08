/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:23:30 by afanti            #+#    #+#             */
/*   Updated: 2023/04/07 02:15:36 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo{
	pthread_t		thread;
	int				id;
	int				eat_nbr;
	long long		last_eat;
	int				left_fork;
	int				right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data{
	int				philo_nbr;
	long			time_to_dead;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_philo_eat;
	long long		first_time;
	long long		last_time;
	pthread_mutex_t	sl;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int			ft_atoi(const char *str);
long long	get_time(void);
int			comp(char *str, char *st);
int			check_av(char **av);
void		initialization(char **av, t_data *data);
void		print_error(char *str);
void		*function(void *data);
void		to_sleep(long time);
void		print_message(char *str, t_philo *philo);

#endif
