/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:56:26 by asyed             #+#    #+#             */
/*   Updated: 2025/07/27 17:51:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *monitor_philosophers(void *arg)
{
	t_table *table = (t_table *)arg;
	int full_count;

	while (1)
	{
		/* Check if someone already died */
		if (has_someone_died(table))
			return NULL;

		full_count = monitor_each_philosopher(table);
		if (full_count == -1) // Death was detected
			return NULL;

		/* If there is a meal limit and every philosopher is full, exit monitor */
		if (table->meals_required > 0 && full_count == table->num_philosophers)
		{
			// Make sure to exit cleanly when all philosophers have eaten enough
			pthread_mutex_lock(&table->print_lock);
			printf(G "✅ 🍽️  All philosophers have eaten %d meals each. Ending simulation.\n" RST,
				table->meals_required);
			pthread_mutex_unlock(&table->print_lock);
			return NULL;
		}

		/* Sleep shorter to detect death more promptly */
		usleep(1000);  // sleep 1 ms
	}
	/* In case the loop exits (for compiler compliance) */
	return NULL;
}

int	has_someone_died(t_table *table)
{
	pthread_mutex_lock(&table->death_lock);
	if (table->someone_died)
	{
		pthread_mutex_unlock(&table->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->death_lock);
	return (0);
}

int	monitor_each_philosopher(t_table *table)
{
	int	i;
	int	full_count;
	long	now;
	long	last_meal;
	int	meals_eaten;

	i = 0;
	full_count = 0;

	while (i < table->num_philosophers)
	{
		now = get_current_time();
		/* Safely read each philosopher's last_meal_time and meals_eaten */
		pthread_mutex_lock(&table->philosophers[i].meal_lock);
		last_meal = table->philosophers[i].last_meal_time;
		meals_eaten = table->philosophers[i].meals_eaten;
		pthread_mutex_unlock(&table->philosophers[i].meal_lock);

		/* Count philosophers who have eaten enough */
		if (table->meals_required > 0 && meals_eaten >= table->meals_required)
			full_count++;

		/* If a philosopher hasn't eaten within time_to_die, signal death */
		if (now - last_meal >= table->time_to_die)
		{
			signal_death(table, i, now);
			return (-1);
		}
		i++;
	}
	return (full_count);
}

void	signal_death(t_table *table, int i, long now)
{
	pthread_mutex_lock(&table->death_lock);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->death_lock);

	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d died\n", now - table->start_time, table->philosophers[i].id);
	pthread_mutex_unlock(&table->print_lock);
}

void	destroy_mutexes(t_table *table)
{
	int i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->philosophers[i].meal_lock);
		pthread_mutex_destroy(&table->forks[i++]);
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
}
