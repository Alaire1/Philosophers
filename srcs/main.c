#include "../include/philo.h"

int ft_exit(char *str) 
{
    printf("Error:%s\n", str);
   	return (0);
}

int	check_death2(t_p *p)
{
	pthread_mutex_lock(&p->a.dead);
	if (p->a.stop)
	{
		pthread_mutex_unlock(&p->a.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->a.dead);
	return (0);
}

void	stop(t_p *p)
{
	int	i;

	i = -1;
	while (!check_death2(p))
		ft_usleep(1);
	while (++i < p->a.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->a.write_mutex);
	i = -1;
	while (++i < p->a.total)
		pthread_mutex_destroy(&p->ph[i].left_fork);
	if (p->a.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->a.meals_to_eat);
	free(p->ph);
}



int	error_msg(char *str)
{
	printf("%sError: %s%s\n", RED, str, RESET);
	return (0);
}

int	main(int argc, char **argv)
{
	t_p		p;
	(void)argc;

	check_argc(argc);
	if (check_argv(argv) == 1)
		return (1);
	if (!(init_struct(argv, &p)))
		return (ft_exit("Invalid Arguments\n"));
	p.ph = malloc(sizeof(t_philo) * p.a.total);
	if (!p.ph)
		return (ft_exit("Malloc returned NULL\n"));
	if (!initialize(&p) || !threading(&p))
	{
		free(p.ph);
		return (0);
	}
	stop(&p);
}