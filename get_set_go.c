/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:27:41 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/31 14:00:29 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// getters and setters (copy = getters,paste = setters)
// automacially lock and unlock mutexes to avoid deadlock
bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	result;

	safe_mutex(mutex, LOCK);
	result = *value;
	safe_mutex(mutex, UNLOCK);
	return (result);
}

void	set_bool(t_mutex *mutex, bool *dst, bool value)
{
	safe_mutex(mutex, LOCK);
	*dst = value;
	safe_mutex(mutex, UNLOCK);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	result;

	safe_mutex(mutex, LOCK);
	result = *value;
	safe_mutex(mutex, UNLOCK);
	return (result);
}

void	set_long(t_mutex *mutex, long *dst, long value)
{
	safe_mutex(mutex, LOCK);
	*dst = value;
	safe_mutex(mutex, UNLOCK);
}
