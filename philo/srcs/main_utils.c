/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:00:59 by asyed             #+#    #+#             */
/*   Updated: 2025/08/13 13:45:21 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	run_simulation(t_table *table)
{
	pthread_t	monitor_thread;


	if (start_simulation(table) != 0)
		return (print_and_return_error("Thread creation failed."));

	/* Create the monitor thread */
	if (pthread_create(&monitor_thread, NULL, monitor_philosophers, table) != 0)
		return (print_and_return_error("Monitor thread creation failed."));

	/* Join all philosopher threads */
	join_philosophers_threads(table);
	/* Join monitor thread */
	pthread_join(monitor_thread, NULL);
	check_simulation_end(table);
	return(0);
}

void	join_philosophers_threads(t_table	*table)
{
	int			join_index;

	join_index = 0;
	while (join_index < table->num_philo)
	{
		pthread_join(table->philosophers[join_index].thread, NULL);
		join_index++;
	}

}

void	check_simulation_end(t_table *table)
{
	int total_meals;
	long timestamp;
	int clean_end;

	/* Count the total meals served */
	total_meals = count_total_meals(table);
	clean_end = simulation_clean_end(table);


	if (table->meals_required > 0 && clean_end)
	{
		timestamp = get_current_time() - table->start_time;
		printf(G "✅ 🍽️  Timestamp: %ld — All %d philosophers have eaten %d times. Ending routine.\n" RST,
			timestamp, table->num_philo, table->meals_required);
		printf(G "✅ 🍴 Total meals served: %d\n" RST, total_meals);
	}
	else if (!clean_end)
	{
		print_valid("💔 Simulation ended early due to a philosopher's death.");
	}
}

int	count_total_meals(t_table *table)
{

	int		meal_index;
	int		total_meals;

	meal_index = 0;
	total_meals = 0;
	while (meal_index < table->num_philo)
	{
		total_meals += table->philosophers[meal_index].meals_eaten;
		meal_index++;
	}
	return(total_meals);
}

int	simulation_clean_end(t_table	*table)
{
	int	is_clean_end;
	/* Check whether simulation ended cleanly (no one died) */
	pthread_mutex_lock(&table->death_lock);
	is_clean_end = (table->someone_died == 0);
	pthread_mutex_unlock(&table->death_lock);

	return(is_clean_end);
}
