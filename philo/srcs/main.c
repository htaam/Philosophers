/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:50:08 by tmatias           #+#    #+#             */
/*   Updated: 2021/07/29 16:30:54 by tmatias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cenas(int	i)
{
	ft_putnbr_fd(i, 1);
}

int	main(void)
{
	int	i;

	i = 0;
	while (i <= 2)
	{
		cenas(i);
		i++;
	}
	exit (0);
}
