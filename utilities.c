/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:35:44 by jlager            #+#    #+#             */
/*   Updated: 2025/07/31 13:57:38 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	return_error(const char *error_msg)
{
	printf(R "❗️%s❗️\n" RESET, error_msg);
	exit(EXIT_FAILURE);
}

bool	finished_simulation(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->finish));
}

long	get_time(t_time time)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL))
		return_error(R"Could not get time of day"RESET);
	if (time == SECONDS)
		return (time_value.tv_sec + (time_value.tv_usec / 1000000));
	else if (time == MILISECONDS)
		return ((time_value.tv_sec * 1000) + (time_value.tv_usec / 1000));
	else if (time == MICROSECONDS)
		return ((time_value.tv_sec * 1000000) + time_value.tv_usec);
	else
		return_error(R"Wrong time input"RESET);
	return (-1);
}

// from manual:
// gettimeofday(struct timeval *restrict te, void *restrict tzp);
// struct timeval
// {
// 	time_t tv_sec; // seconds since Jan. 1st 1970
// 	suseconds_t tv_usec; // and microseconds
// };

// more precise
void	better_usleep(long microseconds, t_table *table)
{
	long	time_start;
	long	time_passed;
	long	time_remaining;

	time_start = get_time(MICROSECONDS);
	while ((get_time(MICROSECONDS) - time_start) < microseconds)
	{
		if (finished_simulation(table))
			break ;
		time_passed = get_time(MICROSECONDS) - time_start;
		time_remaining = microseconds - time_passed;
		if (time_remaining > 1000)
			usleep(time_remaining / 2);
		else
		{
			while ((get_time(MICROSECONDS) - time_start) < microseconds)
				;
		}
	}
}

void	cleanup_and_exit(t_table *table)
{
	t_philosophers	*philosopher;
	int				i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		philosopher = table->philosopher + i;
		safe_mutex(&philosopher->philosopher_mutex, DESTROY);
		i++;
	}
	safe_mutex(&table->printing_lock_mutex, DESTROY);
	safe_mutex(&table->table_mutex, DESTROY);
	free(table->fork);
	free(table->philosopher);
}
