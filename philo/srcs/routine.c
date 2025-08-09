/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:40:10 by asyed             #+#    #+#             */
/*   Updated: 2025/07/27 17:51:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int eating(t_philosopher *philo)
{
	int meal_limit_reached;

	print_status(philo, "is eating");

	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	meal_limit_reached = (philo->table->meals_required > 0 &&
		philo->meals_eaten >= philo->table->meals_required);
	pthread_mutex_unlock(&philo->meal_lock);

	/* Only sleep if time_to_eat > 0 */
	if (philo->table->time_to_eat > 0)
		usleep(philo->table->time_to_eat * 1000);

	unlock_forks(philo);

	/* If meal limit is reached for this philosopher, return 1 */
	return (meal_limit_reached);
}

void sleeping(t_philosopher *philo)
{
	print_status(philo, "is sleeping");

	/* Only sleep if time_to_sleep > 0 */
	if (philo->table->time_to_sleep > 0)
		usleep(philo->table->time_to_sleep * 1000);

	/* When time_to_sleep is 0, add a small yield to prevent CPU hogging */
	else
		usleep(500); /* Small yield of 0.5ms to prevent overwhelming the CPU */
}

void thinking(t_philosopher *philo)
{
	print_status(philo, "is thinking");

	/* Add a small delay for odd-numbered philosophers to break symmetry and deadlock */
	if (philo->id % 2 == 1)
		usleep(500);

	/* If both eating and sleeping times are zero, add an extra delay to prevent starvation */
	if (philo->table->time_to_eat == 0 && philo->table->time_to_sleep == 0)
		usleep(1000);
}
