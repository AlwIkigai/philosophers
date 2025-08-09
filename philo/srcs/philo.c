/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:51:59 by asyed             #+#    #+#             */
/*   Updated: 2025/07/27 17:51:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
** philosopher_routine: a minimal routine for testing.
** It prints a status message and then exits.
*/

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = arg;
    int meal_limit_reached;

    /* Stagger start times to prevent all philosophers from trying to eat at the same time */
    if (philo->id % 2 == 0)
        usleep(1000); /* Small delay for even-numbered philosophers */
    else
        usleep(500);  /* Smaller delay for odd-numbered philosophers */

    /* Special case for single philosopher (can never get both forks) */
    if (philo->table->num_philosophers == 1)
    {
        print_status(philo, "has taken a fork");
        usleep(philo->table->time_to_die * 1000);
        return NULL;
    }

    while (!has_someone_died(philo->table))
    {
        /* Check if we've reached the meal limit */
        pthread_mutex_lock(&philo->meal_lock);
        if (philo->table->meals_required > 0 &&
            philo->meals_eaten >= philo->table->meals_required)
        {
            pthread_mutex_unlock(&philo->meal_lock);
            return NULL;  /* Exit if meal limit reached */
        }
        pthread_mutex_unlock(&philo->meal_lock);

        /* Check if this philosopher needs to eat urgently */
        long current_time = get_current_time();
        pthread_mutex_lock(&philo->meal_lock);
        long time_since_last_meal = current_time - philo->last_meal_time;
        pthread_mutex_unlock(&philo->meal_lock);

        /* If philosopher is at risk of starving, wait less time between attempts */
        long wait_time = 500;
        if (time_since_last_meal > (philo->table->time_to_die * 3) / 4)
            wait_time = 100; /* Very short wait if at risk of dying */

        /* Try to take both forks */
        if (take_forks(philo))
        {
            meal_limit_reached = eating(philo);

            if (meal_limit_reached)
                return NULL;

            sleeping(philo);
            thinking(philo);
        }
        else
        {
            /* If couldn't get both forks, wait a bit before trying again */
            usleep(wait_time);
        }
    }
    return NULL;
}


int check_if_dead(t_philosopher *philo)
{
    if (has_someone_died(philo->table))
    {
        return (1);
    }
    return (0);
}


int take_forks(t_philosopher *philo)
{
    /* Different fork-taking order based on philosopher ID to prevent deadlock */
    if (philo->id % 2 == 0)
        return (lock_left_then_right(philo));
    else
        return (lock_right_then_left(philo));
}

int lock_left_then_right(t_philosopher *philo)
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

int lock_right_then_left(t_philosopher *philo)
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

void unlock_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
