/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_thread_mutex_malloc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:20:59 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/30 15:26:31 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (bytes == 0 || !result)
		return_error("Error at malloc");
	return (result);
}

static void	mutex_error(int status)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
		return_error("Mutex returning error: value specified is invalid");
	else if (status == EDEADLK)
		return_error("Mutex returning error: deadlock, thread blocked");
	else if (status == EPERM)
		return_error("Mutex returning error: thread not holding lock");
	else if (status == ENOMEM)
		return_error("Mutex returning error: not enough memory");
	else if (status == EBUSY)
		return_error("Mutex returning error: mutex locked");
}

void	safe_mutex(t_mutex *mutex, t_code code)
{
	if (code == LOCK)
		mutex_error(pthread_mutex_lock(mutex));
	else if (code == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex));
	else if (code == INIT)
		mutex_error(pthread_mutex_init(mutex, NULL));
	else if (code == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex));
	else
		return_error("Wrong mutex code");
}

static void	thread_error(int status)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		return_error("Thread returning error: no recourses to create thread");
	else if (status == EPERM)
		return_error("Thread returning error: missing permissions");
	else if (status == EINVAL)
		return_error("Thread returning error: value specified is invalid");
	else if (status == ESRCH)
		return_error("Thread returning error: thread with this ID not found");
	else if (status == EDEADLK)
		return_error("Thread returning error: deadlock, thread blocked");
}

void	safe_thread(t_thread *thread, void *(*ops)(void *), void *data,
		t_code code)
{
	if (code == CREATE)
		thread_error(pthread_create(thread, NULL, ops, data));
	else if (code == JOIN)
		thread_error(pthread_join(*thread, NULL));
	else if (code == DETACH)
		thread_error(pthread_detach(*thread));
	else
		return_error("Wrong thread code");
}
