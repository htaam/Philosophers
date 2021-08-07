#include "philo.h"

void	go_to_sleep(int id)
{
	struct timeval	current;

	while (true)
	{
		gettimeofday(&current, NULL);
		check_all_death();
		if (time_difrence_in_ms(g_params.finish_eating[id - 1], current)
			>= g_params.t_2_sleep)
			break ;
	}
	write_message(id, "is thinking");
}
