/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:16:57 by asyed             #+#    #+#             */
/*   Updated: 2025/08/13 17:24:29 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
** init_simulation: initializes the simulation parameters and resources.
** Parameters:
**   table: pointer to the t_table structure to fill in.
**   ac: argument count from command line.
**   av: argument vector containing simulation parameters.
**
** Steps:
** 1. Parse command-line arguments and store them in table.
** 2. Allocate memory for philosopher array and fork mutexes.
** 3. Initialize mutexes: both the print lock and fork mutexes.
** 4. Set the simulation start time.
*//*
** init_simulation: initializes the simulation parameters and resources.
** Parameters:
**   table: pointer to the t_table structure to fill in.
**   ac: argument count from command line.
**   av: argument vector containing simulation parameters.
**
** Steps:
** 1. Parse command-line arguments and store them in table.
** 2. Allocate memory for philosopher array and fork mutexes.
** 3. Initialize mutexes: both the print lock and fork mutexes.
** 4. Set the simulation start time.
*/

int	init_simulation(t_table *table, int ac, char **av)
{
	if (allocate_values(table, ac, av) != 0)
		return (1);
	if (allocate_memory(table) != 0)
		return (1);
	table->someone_died = 0;
	init_simul_mutex(table);
	table->start_time = get_current_time();
	return (0);
}

/*
** start_simulation: creates threads for each philosopher.
** Initializes philosopher structures and launches threads.
*/
int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].table = table;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1)
			% table->num_philo];
		table->philosophers[i].last_meal_time = table->start_time;
		table->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&table->philosophers[i].meal_lock, NULL);
		if (pthread_create(&table->philosophers[i].thread, NULL,
				philosopher_routine, &table->philosophers[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
