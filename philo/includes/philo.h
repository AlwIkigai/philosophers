/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:28:14 by asyed             #+#    #+#             */
/*   Updated: 2025/08/09 19:55:06 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>	/* for malloc, free */
# include <stdio.h>		/* for printf */
# include <unistd.h>	/* for usleep, write */
# include <string.h>	/* for memset */
# include <sys/time.h>	/* for gettimeofday */
# include <pthread.h>	/* for pthread functions */

# define G "\001\033[32m\002"
# define R "\001\033[31m\002"
# define C "\001\033[36m\002"
# define Y "\001\033[33m\002"
# define B "\001\033[34m\002"
# define M "\001\033[35m\002"
# define RST "\001\033[0m\002"

/* Forward declaration for mutual referencing */
typedef struct s_table	t_table;

/* Struct to store philosopher information */
typedef struct s_philosopher
{
	int				id;			/* Philosopher ID (1 to N) */
	pthread_t		thread;		/* Thread representing the philosopher */
	pthread_mutex_t	*left_fork;	/* Pointer to the left fork mutex */
	pthread_mutex_t	*right_fork;/* Pointer to the right fork mutex */
	pthread_mutex_t	meal_lock;	/* Mutex to protect access to last_meal_time */
	long			last_meal_time;/* Time of last meal (ms since simulation start) */
	int				meals_eaten;/* Count of meals eaten */
	t_table			*table;		/* Pointer to shared table data */
}	t_philosopher;

/* Struct to store table settings and shared resources */
typedef struct s_table
{
	int				num_philosophers;	/* Total number of philosophers */
	int				time_to_die;		/* Time in ms before a philosopher dies */
	int				time_to_eat;		/* Time in ms to eat */
	int				time_to_sleep;		/* Time in ms to sleep */
	int				meals_required;		/* Optional: Number of meals each must eat */
	t_philosopher	*philosophers;		/* Array of philosophers */
	pthread_mutex_t	*forks;				/* Array of fork mutexes (1 per fork) */
	pthread_mutex_t	print_lock;			/* Mutex to protect printing to stdout */
	long			start_time;			/* Simulation start time (in ms) */
	int				someone_died;		/* Flag indicating if a philosopher died */
	pthread_mutex_t	death_lock;			/* Mutex to protect someone_died flag */
	int				timeout_enabled;	/* Flag indicating if timeout is enabled */
	long			timeout_duration;	/* Duration after which simulation times out */
}	t_table;

/* Function prototypes */
/* validate_args.c */
long	ft_atol(const char *nptr);
int		is_numeric(char *str);
int		validate_args(int ac, char **av);
int		validate_values(int ac, char **av);

/* validate_check.c */
int		check_empty_arg(char **av, int i, int j);
int		check_negative(char **av, int i, int j);
int		check_numeric(char **av, int i, int j);
int		check_value_range(char **av, int i, long value);

/* print_utils.c */
void	print_valid(const char *message);
void	print_general_error(const char *message);
void	print_detailed_error(const char *msg, int av, const char *value);
void	print_status(t_philosopher *philo, const char *status);
void	print_args(int ac, char **av);
int		print_and_return_error(const char *message);

/* main_utils.c */
void	set_def_args(int *ac, char ***av); /* remove before submission */
int		run_simulation(t_table *table);
void	join_philosophers_threads(t_table *table);
void	check_simulation_end(t_table *table);
int		count_total_meals(t_table *table);
int		simulation_clean_end(t_table *table);

/* simulation.c */
int		init_simulation(t_table *table, int ac, char **av);
int		start_simulation(t_table *table);

/* init_utils.c */
int		allocate_values(t_table *table, int ac, char **av);
int		allocate_memory(t_table *table);
void	allocate_memory_fail(t_table *table);
void	init_simul_mutex(t_table *table);

/* philo.c */
void	*philosopher_routine(void *arg);
int		check_if_dead(t_philosopher *philo);
int		take_forks(t_philosopher *philo);
int		lock_left_then_right(t_philosopher *philo);
int		lock_right_then_left(t_philosopher *philo);
void	unlock_forks(t_philosopher *philo);

/* routine.c */
int		eating(t_philosopher *philo);
void	sleeping(t_philosopher *philo);
void	thinking(t_philosopher *philo);

/* monitor.c */
void	*monitor_philosophers(void *arg);
int		has_someone_died(t_table *table);
int		monitor_each_philosopher(t_table *table);
void	signal_death(t_table *table, int i, long now);
void	destroy_mutexes(t_table *table);
int		check_timeout(t_table *table);

/* utils.c */
long	get_current_time(void);

#endif
