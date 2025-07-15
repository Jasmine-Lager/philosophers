/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasminelager <jasminelager@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:27:41 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/14 12:30:52 by jasminelage      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// getters and setters (copy = getters,paste = setters)
// automacially lock and unlock mutexes to avoid deadlock
bool copy_bool(t_mutex *mutex, bool *value)
{
	bool result;

	safe_mutex(mutex, LOCK);
	result = *value;
	safe_mutex(mutex, UNLOCK);
	return(result);
}

void paste_bool(t_mutex *mutex, bool *dst, bool value)
{
	safe_mutex(mutex, LOCK);
	*dst = value;
	safe_mutex(mutex, UNLOCK);
}

long copy_long(t_mutex *mutex, long *value)
{
	long result;

	safe_mutex(mutex, LOCK);
	result = *value;
	safe_mutex(mutex, UNLOCK);
	return(result);
}
void paste_long(t_mutex *mutex, long *dst, long value)
{
	safe_mutex(mutex, LOCK);
	*dst = value;
	safe_mutex(mutex, UNLOCK);
}