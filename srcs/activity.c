/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:09:23 by akaraban          #+#    #+#             */
/*   Updated: 2023/09/20 01:02:34 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleep_think(t_philo *philos)
{
	pthread_mutex_lock(&philos->pa->write_mutex);
	print_info(philos, "is sleeping", BG_BLUE);
	pthread_mutex_unlock(&philos->pa->write_mutex);
	ft_usleep(philos->pa->time_of_sleeping);
	pthread_mutex_lock(&philos->pa->write_mutex);
	print_info(philos, "is thinking", BG_GREEN);
	pthread_mutex_unlock(&philos->pa->write_mutex);
}

void	activity(t_philo *philos)
{
	pthread_mutex_lock(&philos->left_fork);
	pthread_mutex_lock(&philos->pa->write_mutex);
	print_info(philos, "has taken a fork", BG_YELLOW);
	pthread_mutex_unlock(&philos->pa->write_mutex);
	if (!philos->right_fork)
	{
		ft_usleep(philos->pa->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philos->right_fork);
	pthread_mutex_lock(&philos->pa->write_mutex);
	print_info(philos, "has taken a fork", BG_YELLOW);
	pthread_mutex_unlock(&philos->pa->write_mutex);
	pthread_mutex_lock(&philos->pa->write_mutex);
	print_info(philos, "is eating", BG_WHITE);
	pthread_mutex_lock(&philos->pa->time_eat);
	philos->ms_eat = actual_time();
	pthread_mutex_unlock(&philos->pa->time_eat);
	pthread_mutex_unlock(&philos->pa->write_mutex);
	ft_usleep(philos->pa->time_of_eating);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(&philos->left_fork);
	sleep_think(philos);
}
