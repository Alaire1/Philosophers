/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:09:32 by akaraban          #+#    #+#             */
/*   Updated: 2023/09/20 01:25:05 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_struct(char **argv, t_main *main)
{
	if (argv[5])
		main->info.meals_to_eat = ft_atoi(argv[5]);
	else
		main->info.meals_to_eat = -1;
	main->info.philos_count = ft_atoi(argv[1]);
	main->info.time_to_die = ft_atoi(argv[2]);
	main->info.time_of_eating= ft_atoi(argv[3]);
	main->info.time_of_sleeping = ft_atoi(argv[4]);
}

void	init_mutex(t_main *main)
{
	pthread_mutex_init(&main->info.write_mutex, NULL);
	pthread_mutex_init(&main->info.time_eat, NULL);
	pthread_mutex_init(&main->info.dead, NULL);
	pthread_mutex_init(&main->info.finish, NULL);
}

// int	init_rest(t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	main->a.start_time = actual_time();
// 	main->a.stop = 0;
// 	main->a.nb_philo_finish = 0;
// 	init_mutex(main);
// 	while (i < main->a.philos_count)
// 	{
// 		main->philo[i].id = i + 1;
// 		main->philo[i].ms_eat = main->a.start_time;
// 		main->philo[i].nb_eat = 0;
// 		main->philo[i].finish = 0;
// 		main->philo[i].right_fork = NULL;
// 		pthread_mutex_init(&main->philo[i].left_fork, NULL);
// 		if (main->a.philos_count == 1)
// 			return (1);
// 		if (i == main->a.philos_count - 1)
// 			main->philo[i].right_fork = &main->philo[0].left_fork;
// 		else
// 			main->philo[i].right_fork = &main->philo[i + 1].left_fork;
// 		i++;
// 	}
// 	return (1);
// }
int init_philosophers(t_main *main) 
{
	int i;

	i = 0;
    while (i < main->info.philos_count)
	{
		main->philo[i].id = i + 1;
		main->philo[i].ms_eat = main->info.start_time;
		main->philo[i].nb_eat = 0;
		main->philo[i].finish = 0;
		main->philo[i].right_fork = NULL;
		pthread_mutex_init(&main->philo[i].left_fork, NULL);
		if (main->info.philos_count == 1)
			return (1);
		if (i == main->info.philos_count - 1)
			main->philo[i].right_fork = &main->philo[0].left_fork;
		else
			main->philo[i].right_fork = &main->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}

int init_rest(t_main *main) 
{
    main->info.start_time = actual_time();
    main->info.stop = 0;
    main->info.nb_philo_finish = 0;
    init_mutex(main);
	return(init_philosophers(main));
}