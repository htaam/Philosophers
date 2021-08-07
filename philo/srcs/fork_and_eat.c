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
	struct timeval	current;
	struct timeval	eat_start;

	gettimeofday(&eat_start, NULL);
	gettimeofday(&g_params.last_eaten[id - 1], NULL);
	while (true)
	{
		gettimeofday(&current, NULL);
		check_all_death();
		if (time_difrence_in_ms(eat_start, current)
			>= g_params.t_2_eat)
			break ;
	}
	g_params.times_eaten[id - 1]++;
	gettimeofday(&g_params.finish_eating[id - 1], NULL);
}

void	fork_n_eat1(int id)
{
	struct timeval	current;
	int				left;
	int				right;

	right = id - 1;
	if (id == g_params.n_philo)
		left = 0;
	else
		left = id;
	pthread_mutex_lock(&g_params.fork_mutex[right]);
	gettimeofday(&current, NULL);
	check_all_death();
	write_message(id, "has taken a fork");
	pthread_mutex_lock(&g_params.fork_mutex[left]);
	check_all_death();
	write_message(id, "has taken a fork");
	write_message(id, "is eating");
	eating(id);
	write_message(id, "is sleeping");
	pthread_mutex_unlock(&g_params.fork_mutex[left]);
	pthread_mutex_unlock(&g_params.fork_mutex[right]);
}

void	fork_n_eat2(int id)
{
	struct timeval	current;
	int				left;
	int				right;

	right = id - 1;
	if (id == g_params.n_philo)
		left = 0;
	else
		left = id;
	pthread_mutex_lock(&g_params.fork_mutex[left]);
	gettimeofday(&current, NULL);
	check_all_death();
	write_message(id, "has taken a fork");
	pthread_mutex_lock(&g_params.fork_mutex[right]);
	check_all_death();
	write_message(id, "has taken a fork");
	write_message(id, "is eating");
	eating(id);
	write_message(id, "is sleeping");
	pthread_mutex_unlock(&g_params.fork_mutex[right]);
	pthread_mutex_unlock(&g_params.fork_mutex[left]);
}
