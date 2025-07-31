/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:04:28 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/31 13:38:24 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

// argv[1] = number_of_philosophers >> normal number
// argv[2] = time_to_die >> in ms
// argv[3] = time_to_eat >> in ms
// argv[4] = time_to_sleep >> in ms
// argv[5] = [meals_to_full] >> normal number (optional)

void	parsing(t_table *table, char **argv)
{
	table->number_of_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->meals_to_full = -1;
	if (argv[5])
	{
		table->meals_to_full = ft_atol(argv[5]);
		if (table->meals_to_full <= 0)
			return_error(R"Use only positive numbers"RESET);
		if (table->meals_to_full > 2147483647)
			return_error(R"Number is too big, use INT_MAX or smaller"RESET);
	}
	if (table->number_of_philosophers <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return_error(R"Use only positive numbers"RESET);
	if (table->number_of_philosophers > INT_MAX || table->time_to_die > INT_MAX
		|| table->time_to_eat > INT_MAX || table->time_to_sleep > 2147483647)
		return_error(R"Number is too big, use INT_MAX or smaller"RESET);
	table->time_to_die *= 1000;
	table->time_to_eat *= 1000;
	table->time_to_sleep *= 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		return_error(R"Use timestamps bigger than 60ms"RESET);
}
