/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:40:10 by asyed             #+#    #+#             */
/*   Updated: 2025/08/13 17:44:07 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int perform_philosopher_cycle(t_philosopher *philo)
{
    int meal_limit_reached;

    meal_limit_reached = eating(philo);
    if (meal_limit_reached)
        return (1);
    sleeping(philo);
    thinking(philo);
    return (0);
}
void	stagger_philosopher_start(t_philosopher *philo)
{
    if (philo->id % 2 == 0)
        usleep(1000);
    else
        usleep(500);
}

long calculate_wait_time(t_philosopher *philo, long time_since_last_meal)
{
    if (time_since_last_meal > (philo->table->time_to_die * 3) / 4)
        return (100);
    return (500);
}
long get_time_since_last_meal(t_philosopher *philo)
{
    long current_time;
    long time_since_meal;

    current_time = get_current_time();
    pthread_mutex_lock(&philo->meal_lock);
    time_since_meal = current_time - philo->last_meal_time;
    pthread_mutex_unlock(&philo->meal_lock);
    return (time_since_meal);
}

int check_meal_limit_reached(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->meal_lock);
    if (philo->table->meals_required > 0
        && philo->meals_eaten >= philo->table->meals_required)
    {
        pthread_mutex_unlock(&philo->meal_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->meal_lock);
    return (0);
}

void	*handle_lone_philosopher(t_philosopher *philo)
{
    print_status(philo, "has taken a fork");
    usleep(philo->table->time_to_die * 1000);
    return (NULL);
}

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
