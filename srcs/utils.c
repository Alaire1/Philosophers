#include "../include/philo.h"

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

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		error_msg("Gettimeofday returned -1\n");
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
