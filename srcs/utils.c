/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:09:48 by akaraban          #+#    #+#             */
/*   Updated: 2023/09/20 00:59:32 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		error_msg("Gettimeofday error");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	print_info(t_philo *philos, char *str, const char *colorCode)
{
	long int		time;

	time = actual_time() - philos->pa->start_time;
	if (time >= 0 && time <= 2147483647 && !check_death(philos, 0))
	{
		printf("%ld %d %s%s%s\n", time, philos->id, colorCode, str, RESET);
	}
}
