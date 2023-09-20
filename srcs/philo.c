/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:09:40 by akaraban          #+#    #+#             */
/*   Updated: 2023/09/20 05:11:17 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_for_death2(t_main *main)
{
	pthread_mutex_lock(&main->info.dead);
	if (main->info.stop)
	{
		pthread_mutex_unlock(&main->info.dead);
		return (1);
	}
	pthread_mutex_unlock(&main->info.dead);
	return (0);
}

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->pa->dead);
	if (i)
		philo->pa->stop = i;
	if (philo->pa->stop)
	{
		pthread_mutex_unlock(&philo->pa->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->pa->dead);
	return (0);
}

void	*is_dead(void	*data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->pa->time_to_die + 1);
	pthread_mutex_lock(&ph->pa->time_eat);
	pthread_mutex_lock(&ph->pa->finish);
	if (!check_death(ph, 0) && !ph->finish && ((actual_time() - ph->ms_eat) \
		>= (long)(ph->pa->time_to_die)))
	{
		pthread_mutex_unlock(&ph->pa->time_eat);
		pthread_mutex_unlock(&ph->pa->finish);
		pthread_mutex_lock(&ph->pa->write_mutex);
		print_info(ph, "has died", BG_RED);
		pthread_mutex_unlock(&ph->pa->write_mutex);
		check_death(ph, 1);
	}
	pthread_mutex_unlock(&ph->pa->time_eat);
	pthread_mutex_unlock(&ph->pa->finish);
	return (NULL);
}

void	*start_routine(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->time_of_eating / 10);
	while (!check_death(ph, 0))
	{
		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
		activity(ph);
		pthread_detach(ph->thread_death_id);
		if ((int)++ph->nb_eat == ph->pa->meals_to_eat)
		{
			pthread_mutex_lock(&ph->pa->finish);
			ph->finish = 1;
			ph->pa->nb_philo_finish++;
			if (ph->pa->nb_philo_finish == ph->pa->philos_count)
			{
				pthread_mutex_unlock(&ph->pa->finish);
				check_death(ph, 2);
			}
			pthread_mutex_unlock(&ph->pa->finish);
			return (NULL);
		}
	}
	return (NULL);
}
