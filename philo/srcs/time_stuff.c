#include "philo.h"

int	time_difrence_in_ms(struct timeval start_time, struct timeval end_time)
{
	int	start;
	int	end;

	start = (start_time.tv_sec * 1000000 + start_time.tv_usec) / 1000;
	end = (end_time.tv_sec * 1000000 + end_time.tv_usec) / 1000;
	return (end - start);
}
