#include "philo.h"

void	optional_input(int argc, char **argv)
{
	if (argc == 6)
	{
		if (!ft_string_is_positive_number(argv[5]))
		{
			ft_putstr_fd("\nInvalid input\nPlease use the following format:\n", 2);
			ft_putstr_fd("./philo number_of_philosophers ", 2);
			ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
			ft_exit("(optional)number_of_times_each_philosopher_must_eat\n");
		}
		else
			g_params.optional = ft_atoi(argv[5]);
	}
	if (g_params.n_philo == 1)
	{
		printf("0\t1\thas taken a fork\n");
		usleep(g_params.t_2_die * 1000);
		printf("%d\t1\thas died\n", g_params.t_2_die);
		exit(0);
	}
}

void	handle_inputs(int argc, char **argv)
{
	g_params.optional = 2147483647 - 1;
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("\nInvalid input\nPlease use the following format:\n", 2);
		ft_putstr_fd("./philo number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to", 2);
		ft_exit("_sleep (optional)number_of_times_each_philosopher_must_eat\n");
	}
	if (!ft_string_is_positive_number(argv[1])
		|| !ft_string_is_positive_number(argv[2])
		|| !ft_string_is_positive_number(argv[3])
		|| !ft_string_is_positive_number(argv[4]))
	{
		ft_putstr_fd("\nInvalid input\nPlease use the following format:\n", 2);
		ft_putstr_fd("./philo number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to", 2);
		ft_exit("_sleep (optional)number_of_times_each_philosopher_must_eat\n");
	}
	g_params.n_philo = ft_atoi(argv[1]);
	g_params.t_2_die = ft_atoi(argv[2]);
	g_params.t_2_eat = ft_atoi(argv[3]);
	g_params.t_2_sleep = ft_atoi(argv[4]);
	optional_input(argc, argv);
}
