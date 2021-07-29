#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft.h"

typedef struct s_params
{
	int	n_philo;
	int	t_2_die;
	int	t_2_eat;
	int	t_2_sleep;
	int	optional;
}			t_params;

#endif