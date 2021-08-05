#include "philo.h"

void	die(int id)
{
	int	time_stamp;

	pthread_mutex_lock(&g_params.write);
	gettimeofday(&g_params.end_time, NULL);
	time_stamp = time_difrence_in_ms(g_params.start_time, g_params.end_time);
	printf("%d\t%d\t%s\n", time_stamp, id, "died");
	g_params.stop = 1;
	pthread_exit(NULL);
	pthread_mutex_unlock(&g_params.write);
}
