/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customer_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:05:26 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/29 14:57:19 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// similarly like waiting for a signal back in minitalk
// "spinlock"
// loops until flag is changed
void	wait_for_everyone(t_table *table)
{
	while (!copy_bool(&table->table_mutex, &table->everyone_ready))
		;
}

void	increase_thread_count(t_mutex *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}

bool	everyone_ready(t_mutex *mutex, long *threads,
		long number_of_philosophers)
{
	bool	result;

	result = false;
	safe_mutex(mutex, LOCK);
	if (*threads == number_of_philosophers)
		result = true;
	safe_mutex(mutex, UNLOCK);
	return (result);
}

bool	philosopher_dead(t_philosophers *philosopher)
{
	long	time_last_eat;
	long	time_to_die;

	if (copy_bool(&philosopher->philosopher_mutex, &philosopher->full))
		return (false);
	time_last_eat = get_time(MILISECONDS)
		- copy_long(&philosopher->philosopher_mutex,
			&philosopher->time_last_eat);
	time_to_die = philosopher->table->time_to_die / 1000;
	if (time_last_eat > time_to_die)
		return (true);
	else
		return (false);
}

void	*customer_service(void *value)
{
	int		i;
	t_table	*table;

	table = (t_table *)value;
	while (!everyone_ready(&table->table_mutex, &table->threads_count,
			table->number_of_philosophers))
		;
	while (!finished_simulation(table))
	{
		i = 0;
		while (i < table->number_of_philosophers && !finished_simulation(table))
		{
			if (philosopher_dead(table->philosopher + i))
			{
				paste_bool(&table->table_mutex, &table->finish, true);
				print_status(DEAD, table->philosopher + i, DEBUG_MODE);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
