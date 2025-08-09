/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:27:12 by asyed             #+#    #+#             */
/*   Updated: 2025/08/09 18:17:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	main(int ac, char **av)
{
	t_table		table;

	if (validate_args(ac, av) != 0)
		return (1);

	/* Initialize simulation (parse arguments, allocate memory, initialize mutexes, etc.) */
	if (init_simulation(&table, ac, av) != 0)
	{
		print_general_error("Simulation initialization failed.");
		return (1);
	}

	/* Create philosopher threads */
	if (run_simulation(&table) != 0)
	{
		print_general_error("Simulation runtime failed.");
		return (1);
	}

	destroy_mutexes(&table);

	/* Free all allocated memory */
	free(table.philosophers);
	free(table.forks);

	return (0);
}


