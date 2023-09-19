#include "../include/philo.h"

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

void	*thread(void *data)
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

int	create_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->a.philos_count)
	{
		main->philo[i].pa = &main->a;
		if (pthread_create(&main->philo[i].thread_id, NULL, thread, &main->philo[i]) != 0)
			return (error_msg("Pthread did not return 0\n"));
		i++;
	}
	return (1);
}
