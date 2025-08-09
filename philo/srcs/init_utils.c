/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:10:22 by asyed             #+#    #+#             */
/*   Updated: 2025/08/03 21:43:13 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	allocate_values(t_table *table, int ac, char **av)
{
	table->num_philosophers = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);

	if (ac == 6)
		table->meals_required = ft_atol(av[5]);
	else
		table->meals_required = -1; // no limits; run until death or external stop
		// This is a sentinel value, used to signal "no meal limit".
	return(0);
}

int	allocate_memory(t_table *table)
{
	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	if (!table->philosophers || !table->forks)
	{
		allocate_memory_fail(table);
		return (1);
	}
	return (0);
}

void	allocate_memory_fail(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
	if (table->forks)
		free(table->forks);
}

void	init_simul_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
		pthread_mutex_init(&table->forks[i++], NULL);
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);
}

// the NULL above as 2nd parameter means use default setting
