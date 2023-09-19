#ifndef PHILO_H
# define PHILO_H

//includes 
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

// Text color macros
# define RESET       "\033[0m"
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// Background color macros
# define BG_RESET          "\033[49m"
# define BG_BLACK          "\033[40m"
# define BG_RED            "\033[41m"
# define BG_GREEN          "\033[42m"
# define BG_YELLOW         "\033[43m"
# define BG_BLUE           "\033[44m"
# define BG_MAGENTA        "\033[45m"
# define BG_CYAN           "\033[46m"
# define BG_WHITE          "\033[47m"

typedef struct s_arg
{
	int						philos_count;
	int						time_to_die;
	int						time_of_eating;
	int						time_of_sleeping;
	int						meals_to_eat;
	long int				start_t;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_philo_finish;
	int						stop;
}							t_arg;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_arg					*pa;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
}							t_philo;

typedef struct s_main
{
	t_philo					*philo;
	t_arg					a;
}							t_main;

// activity.c
void		print_info(t_philo *philos, char *str, const char *colorCode);
void		sleep_think(t_philo *philos);
void		activity(t_philo *philos);

//args.c
void		check_args(int argc, char **argv);
int			check_argv(char **argv);

//init.c
void			init_struct(char **argv, t_main *main);
void		init_mutex(t_main *main);
int			init_rest(t_main *main);

//main.c
int			error_msg(char *str);
int			check_for_death2(t_main *main);
void		ft_end(t_main *main);
int			create_philo(t_main *main);
int			main(int argc, char **argv);

//threads.c
void		*is_dead(void	*data);
void		*thread(void *data);
int			create_threads(t_main *main);

//utils_libft.c
int			is_numeric_string(const char *str);
int			ft_atoi(const char *str);
void		ft_mainutchar_fd(char c, int fd);
void		ft_mainutnbr_fd(long int ln, int fd);
int			ft_strlen(char *str);
//+ 2 static functions

//utils.c
int			check_death(t_philo *philos, int i);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
#endif