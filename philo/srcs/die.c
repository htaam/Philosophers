#include "philo.h"

void	die(int id)
{
	int	time_stamp;

	pthread_mutex_lock(&g_params.write);
	gettimeofday(&g_params.end_time, NULL);
	time_stamp = time_difrence_in_ms(g_params.start_time, g_params.end_time);
	if (!g_params.stop)
		printf("%d\t%d\t%s\n", time_stamp, id, "died");
	g_params.stop = 1;
	pthread_mutex_unlock(&g_params.write);
}

void	check_all_death(void)
{
	struct timeval	current;
	int				i;

	i = 1;
	while (i <= g_params.n_philo)
	{
		gettimeofday(&current, NULL);
		if (time_difrence_in_ms(g_params.last_eaten[i - 1], current)
			>= g_params.t_2_die && g_params.times_eaten[i - 1]
			< g_params.optional)
			die(i);
		i++;
	}
}
