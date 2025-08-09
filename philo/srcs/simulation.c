/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:16:57 by asyed             #+#    #+#             */
/*   Updated: 2025/08/03 21:43:13 by asyed            ###   ########.fr       */
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
	// parse command line arguments
	if (allocate_values(table, ac, av) != 0)
		return (1);
	if (allocate_memory(table) != 0)
		return (1);
	table->someone_died = 0;

	// Initialize the print_lock mutex.
    // This mutex is used to synchronize printing to avoid output interleaving.

	// Initialize each fork mutex in a loop.
	// Important part, if not initialise will cause undefined behaviour
	// Lead to crashes or data races
	init_simul_mutex(table);

	// Record the simulation start time.
	table->start_time = get_current_time();
	return (0); // Initialization succeeded.
}


/*
** start_simulation: creates threads for each philosopher.
** Initializes philosopher structures and launches threads.
*/
int start_simulation(t_table *table)
{
    int i;

    i = 0;
	// philosophers array is zero-indexed
    while (i < table->num_philosophers)
    {
        table->philosophers[i].id = i + 1;
		// each gets pointer to shared table struct
		// how access shared resources like forks and config values
        table->philosophers[i].table = table;
        // Set the left fork pointer.
		// if id 1, left 0 and right 1
        table->philosophers[i].left_fork = &table->forks[i];
        // For circular arrangement, the right fork is the next one, with wrap-around.
		// Id 5 is right fork will be 0
        table->philosophers[i].right_fork = &table->forks[(i + 1) % table->num_philosophers];
		// Initialize the last meal time to the simulation start time.
		// Track when they last ate and how many meals they've had
        table->philosophers[i].last_meal_time = table->start_time;
        table->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&table->philosophers[i].meal_lock, NULL);
        // Create the thread that runs philosopher_routine.
        if (pthread_create(&table->philosophers[i].thread, NULL,
                philosopher_routine, &table->philosophers[i]) != 0)
            return (1); // Thread creation failed.
        i++;
    }
	// maybe remove below
	// pthread_mutex_lock(&table->print_lock);
	// print_valid("Simulation initialization and thread creation successful.");
	// pthread_mutex_unlock(&table->print_lock);
    return (0); // All threads created successfully.
}
