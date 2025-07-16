/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasminelager <jasminelager@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:31:04 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/16 13:50:32 by jasminelage      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_to_full]
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		return_error(R "Wrong input... \n"
			RESET G "Correct:"
			RESET "number_of_philosophers time_to_die time_to_eat"
			"time_to_sleep (meals_to_full)\n");
	}
	if (argc == 5 || argc == 6)
	{
		parsing(&table, argv);
		initialize(&table);
		start_simulation(&table);
//		cleanup_and_exit(&table); // if philos are full or one philo dies,
									// otherwise endless
		return (0);
	}
}

// if (argc == 5 || argc == 6)
// {

// }