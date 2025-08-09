/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:08:45 by asyed             #+#    #+#             */
/*   Updated: 2025/08/03 21:14:00 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// the following is for testing purpose
#define STRINGIFY(x) #x
// FOR AUTOMATED TEST CASE NEED TO DO THE FOLLOWING

// int	main(int ac, char **av)
// {

// 	// automated test case
// 	(void)ac;
// 	(void)av;
// 	test_args();
// 	return (0);
// }

void	print_arguments(char **args)
{
	int	i;

	i = 0;
	printf("Arguments: ");
	while (args[i] != NULL)
	{
		printf("\"%s\"", args[i]);
		if (args[i + 1] != NULL)
			printf(", ");
		i++;
	}
	printf(", \n");
}
void	test_args(void)
{
    /* Define test argument arrays with NULL terminators */
    char *too_few[]       = {"./philo", "5", "800", "200", NULL};
    char *too_many[]      = {"./philo", "5", "800", "200", "200", "3", "extra", NULL};
    char *negative[]      = {"./philo", "5", "800", "200", "-200", NULL};
    char *non_numeric[]   = {"./philo", "5", "800", "200", "abc", NULL};
    char *no_optional[]   = {"./philo", "5", "800", "200", "200", NULL};
    char *with_optional[] = {"./philo", "5", "800", "200", "200", "3", NULL};

    char **test_cases[] = {
        too_few,
        too_many,
        negative,
        non_numeric,
        no_optional,
        with_optional
    };
    int test_ac[] = {4, 7, 5, 5, 5, 6};

    char *test_names[] = {
        STRINGIFY(too_few),
        STRINGIFY(too_many),
        STRINGIFY(negative),
        STRINGIFY(non_numeric),
        STRINGIFY(no_optional),
        STRINGIFY(with_optional)
    };

    int i;
    int num_of_tests = 6;
    int ret;

    i = 0;
    while (i < num_of_tests)
    {
        int test_number = i + 1;
        printf("Test %d (%s): \n", test_number, test_names[i]);
		print_arguments(test_cases[i]);
        ret = validate_args(test_ac[i], test_cases[i]);
        if (ret == 0)
            print_valid("Passed\n");
        else
            print_general_error("Failed\n");
        i++;
    }
}
