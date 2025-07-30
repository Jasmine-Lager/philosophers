/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilizing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:03:06 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/30 15:15:46 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// checking philolosopher id to see if its odd or even
// based on that he tries to take fork (either it has been taken on not yet)
void	assing_fork(t_philosophers *philosopher, t_forks *fork, int chair)
{
	int	number_of_philosophers;

	number_of_philosophers = philosopher->table->number_of_philosophers;
	if (philosopher->id % 2 == 1)
	{
		philosopher->left_fork = &fork[(chair + 1) % number_of_philosophers];
		philosopher->right_fork = &fork[chair];
	}
	else
	{
		philosopher->left_fork = &fork[chair];
		philosopher->right_fork = &fork[(chair + 1) % number_of_philosophers];
	}
}

void	init_philosophers(t_table *table)
{
	int				i;
	t_philosophers	*philosopher;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		philosopher = table->philosopher + i;
		philosopher->id = i + 1;
		philosopher->full = false;
		philosopher->meals_count = 0;
		philosopher->table = table;
		safe_mutex(&philosopher->philosopher_mutex, INIT);
		assing_fork(philosopher, table->fork, i);
		i++;
	}
}

void	initialize(t_table *table)
{
	int	i;

	table->finish = false;
	table->everyone_ready = false;
	table->threads_count = 0;
	table->philosopher = safe_malloc(sizeof(t_philosophers)
			* table->number_of_philosophers);
	safe_mutex(&table->table_mutex, INIT);
	safe_mutex(&table->printing_lock_mutex, INIT);
	table->fork = safe_malloc(sizeof(t_forks) * table->number_of_philosophers);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		safe_mutex(&table->fork[i].fork, INIT);
		table->fork[i].fork_id = i;
		i++;
	}
	init_philosophers(table);
}
