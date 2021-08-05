#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft.h"
# include <stdbool.h>

typedef struct s_params
{
	int				n_philo;
	int				t_2_die;
	int				t_2_eat;
	int				t_2_sleep;
	int				optional;
	int				*times_eaten;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	get_time;
	pthread_mutex_t	write;
	struct timeval	start_time;
	struct timeval	end_time;
	struct timeval	last_time;
	struct timeval	*last_eaten;
	struct timeval	*last_sleep;
	int				stop;
}			t_params;

extern t_params	g_params;

void	fork_n_eat1(int id);
void	fork_n_eat2(int id);
int		time_difrence_in_ms(struct timeval start_time, struct timeval end_time);
void	write_message(int id, char	*str);
void	try_to_eat(int id);
void	go_to_sleep(int id);
void	die(int id);

#endif