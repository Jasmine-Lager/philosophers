/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:28:11 by jlager            #+#    #+#             */
/*   Updated: 2025/07/31 13:57:16 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philosopher(void *data)
{
	t_philosophers	*philosopher;

	philosopher = (t_philosophers *)data;
	wait_for_everyone(philosopher->table);
	set_long(&philosopher->philosopher_mutex, &philosopher->time_last_eat,
		get_time(MILISECONDS));
	increase_thread_count(&philosopher->table->table_mutex,
		&philosopher->table->threads_count);
	print_status(TAKE_LEFT_FORK, philosopher, DEBUG_MODE);
	while (!finished_simulation(philosopher->table))
		better_usleep(200, philosopher->table);
	return (NULL);
}
