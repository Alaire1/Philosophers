#include "../include/philo.h"

// int check_values(t_main *main, char **argv)
// {
// 	if (main->a.philos_count <= 0 || main->a.time_to_die <=  0 || main->a.time_of_eating <= 0 \
// 			|| main->a.time_of_sleeping <= 0)
// 		return (1);
// 	if (argv[5] && main->a.meals_to_eat <= 0)
// 		return (1);
// 	return (0);
// }

void	init_struct(char **argv, t_main *main)
{
	if (argv[5])
		main->a.meals_to_eat = ft_atoi(argv[5]);
	else
		main->a.meals_to_eat = -1;
	main->a.philos_count = ft_atoi(argv[1]);
	main->a.time_to_die = ft_atoi(argv[2]);
	main->a.time_of_eating= ft_atoi(argv[3]);
	main->a.time_of_sleeping = ft_atoi(argv[4]);
	// if (check_values(main, argv) == 1)
	// {
	// 	error_msg("Invalid arguments!");
	// 	return (1);
	// }
}

void	init_mutex(t_main *main)
{
	pthread_mutex_init(&main->a.write_mutex, NULL);
	pthread_mutex_init(&main->a.time_eat, NULL);
	pthread_mutex_init(&main->a.dead, NULL);
	pthread_mutex_init(&main->a.finish, NULL);
}

int	init_rest(t_main *main)
{
	int	i;

	i = 0;
	main->a.start_t = actual_time();
	main->a.stop = 0;
	main->a.nb_philo_finish = 0;
	init_mutex(main);
	while (i < main->a.philos_count)
	{
		main->philo[i].id = i + 1;
		main->philo[i].ms_eat = main->a.start_t;
		main->philo[i].nb_eat = 0;
		main->philo[i].finish = 0;
		main->philo[i].right_fork = NULL;
		pthread_mutex_init(&main->philo[i].left_fork, NULL);
		if (main->a.philos_count == 1)
			return (1);
		if (i == main->a.philos_count - 1)
			main->philo[i].right_fork = &main->philo[0].left_fork;
		else
			main->philo[i].right_fork = &main->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}
