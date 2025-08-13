/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:11:06 by asyed             #+#    #+#             */
/*   Updated: 2025/08/10 16:53:10 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_negative(char **av, int i, int j)
{
	if (av[i][j] == '-')
	{
		if (i == 1)
			print_detailed_error("Num of philo must be > 0", i, av[i]);
		else
			print_detailed_error("Time must be non-negative", i, av[i]);
		return (1);
	}
	return (0);
}

int	check_value_range(char **av, int i, long value)
{
	if (i == 1 && value <= 0)
	{
		print_detailed_error("Num of philo must be > 0", i, av[i]);
		return (1);
	}
	else if (i >= 2 && i <= 4 && value < 60)
	{
		print_detailed_error("Time values should be >= 60ms", i, av[i]);
		return (1);
	}
	else if (i == 5 && value <= 0)
	{
		print_detailed_error("Number of meals must be > 0", i, av[i]);
		return (1);
	}
	return (0);
}

int	check_empty_arg(char **av, int i, int j)
{
	while (av[i][j] == ' ')
		j++;
	if (av[i][j] == '\0')
	{
		print_detailed_error("Empty argument", i, av[i]);
		return (1);
	}
	return (0);
}

int	check_numeric(char **av, int i, int j)
{
	if (!is_numeric(av[i] + j))
	{
		print_detailed_error("Not a valid number", i, av[i]);
		return (1);
	}
	return (0);
}
