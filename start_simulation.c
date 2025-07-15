/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasminelager <jasminelager@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:04:00 by jlager            #+#    #+#             */
/*   Updated: 2025/07/14 16:12:57 by jasminelage      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// similarly like waiting for a signal back in minitalk
// "spinlock"
// loops until flag is changed
void	wait_for_everyone(t_table *table)
{
	while(copy_bool(&table->table_mutex, &table->everyone_ready))
		;
}

static void	eating(t_philosophers *philosopher)
{
	safe_mutex(&philosopher->left_fork->fork, LOCK);
	print_status(TAKE_LEFT_FORK, philosopher, DEBUG_MODE);
	safe_mutex(&philosopher->right_fork->fork, LOCK);
	print_status(TAKE_RIGHT_FORK, philosopher, DEBUG_MODE);
	paste_long(&philosopher->philosopher_mutex, &philosopher->time_last_eat, 
		get_time(MILISECONDS));
	philosopher->meals_count++;
	print_status(EATING, philosopher, DEBUG_MODE);
	better_usleep(philosopher->table->time_to_eat, philosopher->table);
	if (philosopher->table->meals_to_full > 0
		&& philosopher->table->meals_to_full == philosopher->meals_count)
		paste_bool(&philosopher->philosopher_mutex, &philosopher->full, true);
	safe_mutex(&philosopher->left_fork->fork, UNLOCK);
	safe_mutex(&philosopher->right_fork->fork, UNLOCK);
}

static void	thinking(t_philosophers *philosopher)
{
	print_status(THINKIN, philosopher, DEBUG_MODE);
}

void	*dining(void *data)
{
	t_philosophers	*philosopher;

	philosopher = (t_philosophers *)data;
	wait_for_everyone(philosopher->table);
	
	while (!finished_simulation())
	{
		if (philosopher->full)
			break ;
		eating(philosopher);
		print_status(SLEEPING, philosopher, DEBUG_MODE)
		better_usleep(philosopher->table->time_to_sleep, philosopher->table);

		thinking()
	}

	return(NULL);
}

// ./philosophers 5 800 200 200 [5]
// number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_to_full]
void	start_simulation(t_table table)
{
	int	i;

	i = 0;
	if (table->number_of_philosophers == 0)
		return ;
	else if (table->number_of_philosophers == 1)
		;
	else if (table->number_of_philosophers > 1)
	{
		while (i < table->number_of_philosophers)
		{
			safe_thread(&table->philosopher[i].thread_id, dining, 
				&table->philosopher[i], CREATE);
			i++;
		}
	}
	table->start = get_time(MICROSECONDS);
	paste_bool(&table->table_mutex, table->everyone_ready, true);
	i = 0;
	while(i < table->number_of_philosophers)
	{
		safe_thread(table>philosopher[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
