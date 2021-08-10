#include "philo.h"

void	try_to_eat(int id)
{
	if (id % 2 == 0)
		fork_n_eat2(id);
	else
		fork_n_eat1(id);
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
	gettimeofday(&g_params.finish_eating[id - 1], NULL);
}

void	check_done_eating(int id)
{
	g_params.times_eaten[id - 1]++;
	if (g_params.times_eaten[id - 1] == g_params.optional)
	{
		pthread_mutex_lock(&g_params.eaten_times);
		g_params.n++;
		pthread_mutex_unlock(&g_params.eaten_times);
		if (g_params.n >= g_params.n_philo)
		{
			pthread_mutex_lock(&g_params.write);
			g_params.stop = 1;
			pthread_mutex_unlock(&g_params.write);
		}
	}
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
	while (check_two_forks_state(right, left) == 1)
		check_all_death();
	grab_a_fork(right);
	gettimeofday(&current, NULL);
	check_all_death();
	write_message(id, "has taken a fork");
	grab_a_fork(left);
	check_all_death();
	write_message(id, "has taken a fork");
	write_message(id, "is eating");
	check_done_eating(id);
	eating(id);
	write_message(id, "is sleeping");
	release_a_fork(left);
	release_a_fork(right);
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
	while (check_two_forks_state(right, left) == 1)
		check_all_death();
	grab_a_fork(left);
	gettimeofday(&current, NULL);
	check_all_death();
	write_message(id, "has taken a fork");
	grab_a_fork(right);
	check_all_death();
	write_message(id, "has taken a fork");
	write_message(id, "is eating");
	check_done_eating(id);
	eating(id);
	write_message(id, "is sleeping");
	release_a_fork(right);
	release_a_fork(left);
}
