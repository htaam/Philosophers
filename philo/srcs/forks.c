#include "philo.h"

int	check_a_fork_state(int	id)
{
	return (g_params.fork[id].state);
}

void	grab_a_fork(int	id)
{
	pthread_mutex_lock(&g_params.fork_mutex[id]);
	g_params.fork[id].state = 1;
}

void	release_a_fork(int	id)
{
	g_params.fork[id].state = 0;
	pthread_mutex_unlock(&g_params.fork_mutex[id]);
}

/* Only returns 1 if one if in use*/
int	check_two_forks_state(int	id1, int	id2)
{
	if (check_a_fork_state(id1) == 0)
	{
		if (check_a_fork_state(id2) == 0)
			return (0);
	}
	return (1);
}
