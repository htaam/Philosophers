/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:50:08 by tmatias           #+#    #+#             */
/*   Updated: 2021/08/12 18:10:50 by tmatias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* global variable declaration */
t_params		g_params;

void	*philo_tread(void *a)
{
	int			id;

	id = ft_atoi(a);
	free(a);
	while (g_params.n <= g_params.n_philo)
	{
		if (!g_params.stop || g_params.n < g_params.n_philo)
			try_to_eat(id);
		if (!g_params.stop || g_params.n < g_params.n_philo)
			go_to_sleep(id);
		if (g_params.stop || g_params.n >= g_params.n_philo)
			return (0);
	}
	return (0);
}

void	init(void)
{
	int	i;

	i = 1;
	g_params.n = 0;
	gettimeofday(&g_params.start_time, NULL);
	pthread_mutex_init(&g_params.write, NULL);
	pthread_mutex_init(&g_params.eaten_times, NULL);
	g_params.times_eaten = malloc (sizeof(int) * g_params.n_philo);
	g_params.fork_mutex = malloc (sizeof(pthread_mutex_t) * g_params.n_philo);
	g_params.last_eaten = malloc (sizeof(struct timeval) * g_params.n_philo);
	g_params.finish_eating = malloc (sizeof(struct timeval) * g_params.n_philo);
	g_params.last_sleep = malloc (sizeof(struct timeval) * g_params.n_philo);
	g_params.stop = 0;
	g_params.fork = malloc (sizeof(t_fork) * g_params.n_philo);
	while (i <= g_params.n_philo)
	{
		gettimeofday(&g_params.last_eaten[i - 1], NULL);
		g_params.fork[i].state = 0;
		i++;
	}
}

void	end_stuff(void)
{
	int	i;

	i = 1;
	while (i <= g_params.n_philo)
	{
		pthread_mutex_destroy(&g_params.fork_mutex[i - 1]);
		i++;
	}
	pthread_mutex_destroy(&g_params.write);
	pthread_mutex_destroy(&g_params.eaten_times);
	free(g_params.fork_mutex);
	free(g_params.last_eaten);
	free(g_params.finish_eating);
	free(g_params.times_eaten);
	free(g_params.last_sleep);
	free(g_params.fork);
}

int	main(int argc, char **argv)
{
	pthread_t		*philo;
	int				i;
	char			**b;

	handle_inputs(argc, argv);
	init();
	b = malloc(sizeof(char *) * g_params.n_philo);
	philo = malloc(sizeof(pthread_t) * g_params.n_philo);
	i = 1;
	while (i <= g_params.n_philo)
	{
		b[i - 1] = ft_itoa(i);
		g_params.times_eaten[i - 1] = 0;
		pthread_mutex_init(&g_params.fork_mutex[i - 1], NULL);
		pthread_create(&philo[i - 1], NULL, philo_tread, (void *)b[i - 1]);
		i++;
	}
	i = 0;
	while (++i <= g_params.n_philo)
		pthread_join(philo[i - 1], NULL);
	end_stuff();
	free(b);
	free(philo);
	return (0);
}
