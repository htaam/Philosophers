/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:50:08 by tmatias           #+#    #+#             */
/*   Updated: 2021/08/05 20:29:25 by tmatias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* global variable declaration */
t_params		g_params;

void	handle_inputs(int argc, char **argv)
{
	g_params.optional = 200;
	if (argc < 5 || argc > 6)
		ft_exit("Invalid input");
	if (!ft_string_is_positive_number(argv[1])
		|| !ft_string_is_positive_number(argv[2])
		|| !ft_string_is_positive_number(argv[3])
		|| !ft_string_is_positive_number(argv[4]))
		ft_exit("Invalid input");
	g_params.n_philo = ft_atoi(argv[1]);
	g_params.t_2_die = ft_atoi(argv[2]);
	g_params.t_2_eat = ft_atoi(argv[3]);
	g_params.t_2_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (!ft_string_is_positive_number(argv[5]))
			ft_exit("Invalid input");
		else
		{
			g_params.optional = ft_atoi(argv[5]);
			if (g_params.optional < 1)
				ft_exit("One of your parameters has a negative value");
		}
	}
	if (g_params.n_philo < 1 || g_params.t_2_die < 1 || g_params.t_2_eat < 1
		|| g_params.t_2_sleep < 1)
		ft_exit("One of your parameters has a negative value");
}

void	*philo_tread(void *a)
{
	int			id;

	id = ft_atoi(a);
	while (g_params.times_eaten[id - 1] <= g_params.optional)
	{
		if (!g_params.stop)
			try_to_eat(id);
		if (!g_params.stop)
			go_to_sleep(id);
		if (g_params.stop)
			return (0);
		g_params.times_eaten[id - 1]++;
	}
	return (0);
}

void	init(void)
{
	gettimeofday(&g_params.start_time, NULL);
	pthread_mutex_init(&g_params.write, NULL);
	pthread_mutex_init(&g_params.get_time, NULL);
	g_params.times_eaten = malloc (sizeof(int) * g_params.n_philo);
	g_params.fork_mutex = malloc (sizeof(pthread_mutex_t) * g_params.n_philo);
	g_params.last_eaten = malloc (sizeof(struct timeval) * g_params.n_philo);
	g_params.last_sleep = malloc (sizeof(struct timeval) * g_params.n_philo);
	g_params.stop = 0;
}

int	main(int argc, char **argv)
{
	pthread_t		*philo;
	int				i;
	char			*a;

	handle_inputs(argc, argv);
	init();
	philo = malloc(sizeof(pthread_t) * g_params.n_philo);
	i = 1;
	while (i <= g_params.n_philo)
	{
		a = ft_itoa(i);
		g_params.times_eaten[i - 1] = 1;
		gettimeofday(&g_params.last_eaten[i - 1], NULL);
		pthread_mutex_init(&g_params.fork_mutex[i - 1], NULL);
		pthread_create(&philo[i - 1], NULL, philo_tread, (void *)a);
		i++;
	}
	pthread_exit(NULL);
	i = 1;
	while (i <= g_params.n_philo)
	{
		pthread_mutex_destroy(&g_params.fork_mutex[i - 1]);
		i++;
	}
	if (g_params.stop)
		pthread_mutex_unlock(&g_params.write);
	pthread_mutex_destroy(&g_params.write);
	free(philo);
	free(g_params.fork_mutex);
	return (0);
}
