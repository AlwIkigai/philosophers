/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:42:38 by asyed             #+#    #+#             */
/*   Updated: 2025/07/27 17:33:31 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(const char *nptr)
{
	long	num;
	long	sign;

	num = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		nptr++;
	}
	return (num * sign);
}
// helper print function
// valid and invalid arguments

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_values(int ac, char **av)
{
	int		i;
	long	value;

	i = 1;
	while (i < ac)
	{
		if (!is_numeric(av[i]))
		{
			print_detailed_error("Not a valid number", i, av[i]);
			return (1);
		}
		value = ft_atol(av[i]);

		/* First argument (number of philosophers) must be > 0 */
		if (i == 1 && value <= 0)
		{
			print_detailed_error("Number of philosophers must be a positive integer", i, av[i]);
			return (1);
		}
		/* Other arguments (time values) can be 0 or positive */
		else if (i > 1 && value < 0)
		{
			print_detailed_error("Time values must be non-negative integers", i, av[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		print_general_error("Invalid number of arguments");
		print_general_error("Expected 4 or 5 arguments.");
		printf(G "Please input the following arguments:" RST "\n");
		printf(G "<number_of_philosophers>, <time_to_die>, <time_to_eat>, <time_to_sleep>, [optional] <number_of_times_each_philosopher_must_eat>" RST "\n");
		return (1);
	}
	if (validate_values(ac, av))
		return (1);
	return (0);
}
