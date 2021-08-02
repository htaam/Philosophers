/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:50:08 by tmatias           #+#    #+#             */
/*   Updated: 2021/08/02 18:12:35 by tmatias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* global variable declaration */
t_params		g_params;
pthread_mutex_t	*g_lock;

void	handle_inputs(int argc, char **argv)
{
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
	int	id;

	id = ft_atoi(a);
	printf("id = %d\n", id);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*philo;
	int				i;
	char			*a;

	handle_inputs(argc, argv);
	philo = malloc(sizeof(pthread_t) * g_params.n_philo);
	g_lock = malloc (sizeof(pthread_mutex_t) * g_params.n_philo);
	i = 1;
	while (i <= g_params.n_philo)
	{
		a = ft_itoa(i);
		pthread_create(&philo[i], NULL, philo_tread, (void *)a);
		i++;
	}	
	pthread_exit(NULL);
	return (0);
}
