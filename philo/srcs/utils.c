/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:48:40 by asyed             #+#    #+#             */
/*   Updated: 2025/07/27 15:32:58 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
** get_current_time: returns the current time in milliseconds.
** It uses gettimeofday() which fills a timeval struct with seconds and microseconds.
** We convert seconds to milliseconds by multiplying by 1000L (L ensures a long literal)
** and microseconds to milliseconds by dividing by 1000.
*/

long	get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void print_status(t_philosopher *philo, const char *status)
{
	long timestamp;

    if (has_someone_died(philo->table))
        return;

    timestamp = get_current_time() - philo->table->start_time;

    pthread_mutex_lock(&philo->table->print_lock);
    /* Check again in case death occurred while waiting for print_lock */
    if (!has_someone_died(philo->table))
    {
        printf("%ld %d %s\n", timestamp, philo->id, status);
    }
    pthread_mutex_unlock(&philo->table->print_lock);
}
