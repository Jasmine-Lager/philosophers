/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasminelager <jasminelager@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:14:26 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/15 13:23:41 by jasminelage      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Any state change of a philosopher must be formatted as follows:
// - timestamp_in_ms X has taken a fork
// - timestamp_in_ms X is eating
// - timestamp_in_ms X is sleeping
// - timestamp_in_ms X is thinking
// - timestamp_in_ms X died
// Replace timestamp_in_ms with the current timestamp in milliseconds
// and X with the philosopher number.

void	print_status(t_philosopher_status status, t_philosophers *philosopher) 
	// bool bugs)
{
	long	time_passed;

	time_passed = get_time(MILISECONDS) - philosopher->table->start;
	if (philosopher->full)
		return ;
	safe_mutex(&philosopher->table->printing_lock_mutex, LOCK);
	// if (bugs)
	// 	print_bug_warning(status, philosopher, bugs);
	else if (!finished_simulation(philosopher->table))
	{
		// if (status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		// 	printf("%-6ld %d has taken a fork 🥄", time_passed, philosopher->id);
		if (status == TAKE_LEFT_FORK)
			printf("%-6ld %d took left fork 🥄", time_passed, philosopher->id);
		if (status == TAKE_RIGHT_FORK)
			printf("%-6ld %d took right fork 🥄", time_passed, philosopher->id); // for debugging
		else if (status == EATING)
			printf("%-6ld %d is eating 🍽️,\n%ld meals eaten 🍕", time_passed, 
				philosopher->id, philosopher->meals_count);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping 😴", time_passed, philosopher->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking 🤔", time_passed, philosopher->id);
		else if (status == DIED)
			printf(R"%-6ld %d died 🪦"RESET, time_passed, philosopher->id);
	}
	safe_mutex(&philosopher->table->printing_lock_mutex, UNLOCK);
}

// 6ld is for long data type