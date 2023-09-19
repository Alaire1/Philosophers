#include "../include/philo.h"

void	print_info(t_philo *philos, char *str, const char *colorCode)
{
	long int		time;

	// time = -1;
	time = actual_time() - philos->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(philos, 0))
	{
		printf("%ld %d %s%s%s\n", time, philos->id, colorCode, str, RESET);
	}
}

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
