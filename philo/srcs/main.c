/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:27:12 by asyed             #+#    #+#             */
/*   Updated: 2025/08/03 21:24:40 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * Process additional flags like --test that might come after the philosopher arguments
 */
// remove before submission
int process_special_flags(int ac, char **av)
{
	/* Check for --test flag which runs automated tests */
	if (ac == 2 && strcmp(av[1], "--test args") == 0)
	{
		test_args();
		return 1;
	}
	return 0;
}

int	main(int ac, char **av)
{
	t_table		table;

	/* Check for special flags like --test */
	// remove before submission

	if (process_special_flags(ac, av))
		return (0);

	/* Validate arguments */
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


