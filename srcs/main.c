#include "../include/philo.h"

int error_msg(char *str) 
{
   printf("%sError: %s%s\n", RED, str, RESET);
   	return (1);
}

int	check_death2(t_main *main)
{
	pthread_mutex_lock(&main->a.dead);
	if (main->a.stop)
	{
		pthread_mutex_unlock(&main->a.dead);
		return (1);
	}
	pthread_mutex_unlock(&main->a.dead);
	return (0);
}

void	ft_end(t_main *main)
{
	int	i;

	i = -1;
	while (!check_death2(main))
		ft_usleep(1);
	while (++i < main->a.philos_count)
		pthread_join(main->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&main->a.write_mutex);
	i = -1;
	while (++i < main->a.philos_count)
		pthread_mutex_destroy(&main->philo[i].left_fork);
	if (main->a.stop == 2)
		printf("Each philosopher ate %d time(s)\n", main->a.meals_to_eat);
	free(main->philo);
}

int create_philo(t_main *main)
{
    main->philo = malloc(sizeof(t_philo) * main->a.philos_count);
    if (!main->philo) 
	{
		error_msg("Allocation unsuccessfull");
        return (1); 
    }
    return (0);
}


int	main(int argc, char **argv)
{
	t_main		main;

	check_args(argc, argv);
	init_struct(argv, &main);
	if (create_philo(&main) == 1)
		return (1);
	if (!init_rest(&main) || !create_threads(&main))
	{
		free(main.philo);
		return (0);
	}
	ft_end(&main);
}