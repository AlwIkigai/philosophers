/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:26:54 by asyed             #+#    #+#             */
/*   Updated: 2025/05/17 18:13:33 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_valid(const char *message)
{
	printf(C "✅ %s" RST "\n", message);
}

void	print_general_error(const char *message)
{
	printf(M "❌ Error: %s" RST "\n", message);
}

void	print_detailed_error(const char *msg, int av, const char *value)
{
	printf(M "❌ Error: %s (Argument %d: '%s')" RST "\n", msg, av, value);
}

int		print_and_return_error(const char *message)
{
	print_general_error(message);
	return (1);
}

void	print_args(int ac, char **av)
{
	int i = 0;
	while (i < ac)
	{
		printf("av[%d] = %s\n", i, av[i]);
		i++;
	}
}
