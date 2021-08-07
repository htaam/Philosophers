#include "philo.h"

void	write_message(int id, char	*str)
{
	int	time_stamp;

	check_all_death();
	if (g_params.stop)
		return ;
	pthread_mutex_lock(&g_params.write);
	if (g_params.stop)
	{
		pthread_mutex_unlock(&g_params.write);
		return ;
	}
	gettimeofday(&g_params.end_time, NULL);
	time_stamp = time_difrence_in_ms(g_params.start_time, g_params.end_time);
	if (!g_params.stop)
		printf("%d\t%d\t%s\n", time_stamp, id, str);
	pthread_mutex_unlock(&g_params.write);
}
