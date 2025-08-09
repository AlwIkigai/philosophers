/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:42:38 by asyed             #+#    #+#             */
/*   Updated: 2025/08/09 19:18:50 by asyed            ###   ########.fr       */
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
	int		j;
	long	value;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] == ' ')
			j++;
		if (check_empty_arg(av, i, j))
			return (1);
		if (check_negative(av, i, j))
			return (1);
		if (check_numeric(av, i, j))
			return (1);
		value = ft_atol(av[i]);
		if (check_value_range(av, i, value))
			return (1);
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
		printf(G "Please input the following numbers and time:" RST "\n");
		printf(G "<num_of_philo>, <to_die>, <to_eat>, <to_sleep> " RST);
		printf(G "[optional] <num_of_times_each_philo_must_eat>" RST "\n");
		return (1);
	}
	if (validate_values(ac, av))
		return (1);
	return (0);
}
