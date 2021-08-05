#include "philo.h"

void	try_to_eat(int id)
{
	if (id % 2 == 0)
		fork_n_eat1(id);
	else
		fork_n_eat2(id);
}

void	eating(int id)
{
	usleep(g_params.t_2_eat * 1000);
	g_params.times_eaten[id - 1]++;
	gettimeofday(&g_params.last_eaten[id - 1], NULL);
	write_message(id, "is sleeping");
}

void	fork_n_eat1(int id)
{
	struct timeval	current;

	pthread_mutex_lock(&g_params.fork_mutex[id - 1]);
	gettimeofday(&current, NULL);
	if (time_difrence_in_ms(g_params.last_eaten[id - 1], current)
		>= g_params.t_2_die)
	{
		die(id);
		return ;
	}
	write_message(id, "has taken a fork");
	if (id < g_params.n_philo)
	{
		pthread_mutex_lock(&g_params.fork_mutex[id]);
		write_message(id, "has taken a fork");
		write_message(id, "is eating");
		eating(id);
		pthread_mutex_unlock(&g_params.fork_mutex[id]);
	}
	else
	{
		pthread_mutex_lock(&g_params.fork_mutex[0]);
		write_message(id, "has taken a fork");
		write_message(id, "is eating");
		eating(id);
		pthread_mutex_unlock(&g_params.fork_mutex[0]);
	}
	pthread_mutex_unlock(&g_params.fork_mutex[id - 1]);
}

void	fork_n_eat2(int id)
{
	struct timeval	current;

	pthread_mutex_lock(&g_params.fork_mutex[id]);
	gettimeofday(&current, NULL);
	if (time_difrence_in_ms(g_params.last_eaten[id - 1], current)
		>= g_params.t_2_die)
	{
		die(id);
		return ;
	}
	write_message(id, "has taken a fork");
	if (id < g_params.n_philo)
	{
		pthread_mutex_lock(&g_params.fork_mutex[id - 1]);
		write_message(id, "has taken a fork");
		write_message(id, "is eating");
		eating(id);
		pthread_mutex_unlock(&g_params.fork_mutex[id - 1]);
	}
	else
	{
		pthread_mutex_lock(&g_params.fork_mutex[0]);
		write_message(id, "has taken a fork");
		write_message(id, "is eating");
		eating(id);
		pthread_mutex_unlock(&g_params.fork_mutex[0]);
	}
	pthread_mutex_unlock(&g_params.fork_mutex[id]);
}
