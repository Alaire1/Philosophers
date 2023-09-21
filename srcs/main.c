/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:09:36 by akaraban          #+#    #+#             */
/*   Updated: 2023/09/21 05:24:37 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutexes(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->info.philos_count)
	{
		pthread_join(main->philo[i].thread_id, NULL);
		i++;
	}
	pthread_mutex_destroy(&main->info.write_mutex);
	i = 0;
	while (i < main->info.philos_count)
	{
		pthread_mutex_destroy(&main->philo[i].left_fork);
		i++;
	}
}

void	ft_end(t_main *main)
{
	while (!check_for_death2(main))
		ft_usleep(1);
	destroy_mutexes(main);
	if (main->info.stop == 2)
		printf("%sEvery philosopher has eaten%s %s%d%s %stime(s)%s\n",
			GREEN, RESET, YELLOW, main->info.meals_to_eat, RESET, GREEN, RESET);
	free(main->philo);
}

int	create_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->info.philos_count)
	{
		main->philo[i].pa = &main->info;
		if (pthread_create(&main->philo[i].thread_id, NULL, \
		start_routine, &main->philo[i]) != 0)
			return (error_msg("Pthread error\n"));
		i++;
	}
	return (0);
}

int	create_philo(t_main *main)
{
	main->philo = malloc(sizeof(t_philo) * main->info.philos_count);
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
	init_rest(&main);
	if (create_threads(&main) == 1)
	{
		free(main.philo);
		return (0);
	}
	ft_end(&main);
	return (0);
}
