/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:04:00 by jlager            #+#    #+#             */
/*   Updated: 2025/07/31 13:57:25 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fair_waiting(t_philosophers *philosopher)
{
	if (philosopher->table->number_of_philosophers % 2 == 0)
	{
		if (philosopher->id % 2 == 0)
			better_usleep(30000, philosopher->table);
	}
	else if (philosopher->table->number_of_philosophers % 2 != 0)
	{
		if (philosopher->id % 2 != 0)
			thinking(philosopher, true);
	}
}

// dynamic so that they eat asap
void	thinking(t_philosophers *philosopher, bool before_simulation)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	if (before_simulation == false)
		print_status(THINKING, philosopher, DEBUG_MODE);
	if (philosopher->table->number_of_philosophers % 2 == 0)
		return ;
	time_to_eat = philosopher->table->time_to_eat;
	time_to_sleep = philosopher->table->time_to_sleep;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	better_usleep(time_to_think / 2, philosopher->table);
}

void	eating(t_philosophers *philosopher)
{
	safe_mutex(&philosopher->left_fork->fork, LOCK);
	print_status(TAKE_LEFT_FORK, philosopher, DEBUG_MODE);
	safe_mutex(&philosopher->right_fork->fork, LOCK);
	print_status(TAKE_RIGHT_FORK, philosopher, DEBUG_MODE);
	set_long(&philosopher->philosopher_mutex, &philosopher->time_last_eat,
		get_time(MILISECONDS));
	philosopher->meals_count++;
	print_status(EATING, philosopher, DEBUG_MODE);
	better_usleep(philosopher->table->time_to_eat, philosopher->table);
	if (philosopher->table->meals_to_full > 0
		&& philosopher->table->meals_to_full == philosopher->meals_count)
		set_bool(&philosopher->philosopher_mutex, &philosopher->full, true);
	safe_mutex(&philosopher->left_fork->fork, UNLOCK);
	safe_mutex(&philosopher->right_fork->fork, UNLOCK);
}

void	*dining(void *data)
{
	t_philosophers	*philosopher;

	philosopher = (t_philosophers *)data;
	wait_for_everyone(philosopher->table);
	set_long(&philosopher->philosopher_mutex, &philosopher->time_last_eat,
		get_time(MILISECONDS));
	increase_thread_count(&philosopher->table->table_mutex,
		&philosopher->table->threads_count);
	fair_waiting(philosopher);
	while (!finished_simulation(philosopher->table))
	{
		if (philosopher->full)
			break ;
		eating(philosopher);
		print_status(SLEEPING, philosopher, DEBUG_MODE);
		better_usleep(philosopher->table->time_to_sleep, philosopher->table);
		thinking(philosopher, false);
	}
	return (NULL);
}

// ./philosophers 5 800 200 200 [5]
// number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_to_full]
// thinking is the only volatile variable
// THE MAIN THREAD
void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_of_philosophers == 0)
		return ;
	else if (table->number_of_philosophers == 1)
		safe_thread(&table->philosopher[0].thread_id, one_philosopher,
			&table->philosopher[0], CREATE);
	else if (table->number_of_philosophers > 1)
	{
		while (i++ < table->number_of_philosophers - 1)
			safe_thread(&table->philosopher[i].thread_id, dining,
				&table->philosopher[i], CREATE);
	}
	safe_thread(&table->waiter, customer_service, table, CREATE);
	table->start = get_time(MILISECONDS);
	set_bool(&table->table_mutex, &table->everyone_ready, true);
	i = -1;
	while (i++ < table->number_of_philosophers - 1)
		safe_thread(&table->philosopher[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->finish, true);
	safe_thread(&table->waiter, NULL, NULL, JOIN);
}
// please dont kill me for initializing at -1, I would use
// i = 0;
// while (i < table->number_of_philosophers)
// {
// 	safe_thread(&table->philosopher[i].thread_id, dining,
// 		&table->philosopher[i], CREATE);
// 	i++;
// }
