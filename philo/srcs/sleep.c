#include "philo.h"

void	go_to_sleep(int id)
{
	struct timeval	current;

	while (true)
	{
		gettimeofday(&current, NULL);
		if (time_difrence_in_ms(g_params.last_eaten[id - 1], current)
			>= g_params.t_2_die)
		{
			die(id);
			return ;
		}
		if (time_difrence_in_ms(g_params.last_eaten[id - 1], current)
			>= g_params.t_2_sleep)
			break ;
	}
	write_message(id, "is thinking");
}
