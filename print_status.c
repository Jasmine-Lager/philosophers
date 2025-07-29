/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:14:26 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/29 13:04:38 by jlager           ###   ########.fr       */
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

static void	print_debug(t_philosopher_status status,
		t_philosophers *philosopher, long time_stamp)
{
	if (status == TAKE_LEFT_FORK && !finished_simulation(philosopher->table))
		printf(B "%-6ld %d took left fork 🥄, (fork id: %d)" RESET, time_stamp,
			philosopher->id, philosopher->left_fork->fork_id);
	if (status == TAKE_RIGHT_FORK && !finished_simulation(philosopher->table))
		printf(B "%-6ld %d took right fork 🥄, (fork id: %d)" RESET, time_stamp,
			philosopher->id, philosopher->right_fork->fork_id);
	else if (status == EATING && !finished_simulation(philosopher->table))
		printf(B "%-6ld %d is eating 🍽️,\n%ld meals eaten 🍕" RESET, time_stamp,
			philosopher->id, philosopher->meals_count);
	else if (status == SLEEPING && !finished_simulation(philosopher->table))
		printf(B "%-6ld %d is sleeping 😴" RESET, time_stamp, philosopher->id);
	else if (status == THINKING && !finished_simulation(philosopher->table))
		printf(B "%-6ld %d is thinking 🤔" RESET, time_stamp, philosopher->id);
	else if (status == DEAD && !finished_simulation(philosopher->table))
		printf(B "%-6ld %d died 🪦" RESET, time_stamp, philosopher->id);
}

void	print_status(t_philosopher_status status, t_philosophers *philosopher,
		bool debug)
{
	long	time_stamp;

	safe_mutex(&philosopher->table->printing_lock_mutex, LOCK);
	time_stamp = get_time(MILISECONDS) - philosopher->table->start;
	if (philosopher->full)
	{
		safe_mutex(&philosopher->table->printing_lock_mutex, UNLOCK);
		return ;
	}
	if (debug)
		print_debug(status, philosopher, time_stamp);
	if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		&& !finished_simulation(philosopher->table))
		printf("%-6ld %d has taken a fork 🥄", time_stamp, philosopher->id);
	else if (status == EATING && !finished_simulation(philosopher->table))
		printf("%-6ld %d is eating 🍽️,\n%ld meals eaten 🍕", time_stamp,
			philosopher->id, philosopher->meals_count);
	else if (status == SLEEPING && !finished_simulation(philosopher->table))
		printf("%-6ld %d is sleeping 😴", time_stamp, philosopher->id);
	else if (status == THINKING && !finished_simulation(philosopher->table))
		printf("%-6ld %d is thinking 🤔", time_stamp, philosopher->id);
	else if (status == DEAD && !finished_simulation(philosopher->table))
		printf(R"%-6ld %d DEAD 🪦"RESET, time_stamp, philosopher->id);
	safe_mutex(&philosopher->table->printing_lock_mutex, UNLOCK);
}

// -6ld in printf
// -: is left-alignment, by default, output is right-aligned
// 6: defines the minimum number of characters, othervise adding spaces
// l: for long data types
// d: decimal intege