/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:51:59 by asyed             #+#    #+#             */
/*   Updated: 2025/08/13 17:45:47 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
** philosopher_routine: a minimal routine for testing.
** It prints a status message and then exits.
*/

void	*philosopher_routine(void *table_philosopher)
{
	t_philosopher	*philo;
	long			time_since_last_meal;
	long			wait_time;

	philo = table_philosopher;
	stagger_philosopher_start(philo);
	if (philo->table->num_philo == 1)
		return (handle_lone_philosopher(philo));
	while (!has_someone_died(philo->table))
	{
		if (check_meal_limit_reached(philo))
			return (NULL);
		time_since_last_meal = get_time_since_last_meal(philo);
		wait_time = calculate_wait_time(philo, time_since_last_meal);
		if (take_forks(philo))
		{
            if (perform_philosopher_cycle(philo))
                return (NULL);
		}
		else
			usleep(wait_time);
	}
	return (NULL);
}

int	check_if_dead(t_philosopher *philo)
{
	if (has_someone_died(philo->table))
	{
		return (1);
	}
	return (0);
}

int	take_forks(t_philosopher *philo)
{
	/* Different fork-taking order based on philosopher ID to prevent deadlock */
	if (philo->id % 2 == 0)
		return (lock_left_then_right(philo));
	else
		return (lock_right_then_left(philo));
}

int	lock_left_then_right(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	/* Check if death occurred after taking first fork */
	if (has_someone_died(philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	return (1);
}

int	lock_right_then_left(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	/* Check if death occurred after taking first fork */
	if (has_someone_died(philo->table))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	return (1);
}

void	unlock_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
