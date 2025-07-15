/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasminelager <jasminelager@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:31:00 by jasminelage       #+#    #+#             */
/*   Updated: 2025/07/14 16:23:31 by jasminelage      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h> // INT_MAX, INT_MAX
# include <pthread.h>
// mutex: init destroy lock unlock,threads: create join detach
# include <stdbool.h>  // bool flags
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep
// no libft authorization here

// ANSI escape codes for colored text :)
# define R "\x1b[31m"
# define G "\x1b[32m"
# define B "\x1b[34m"
# define RESET "\x1b[0m"

// for more readable code; renaming
// mutex = MUTual EXclusion object = "reserves" global variables
// "global intiger value"
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef enum 			e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_code;

typedef enum 			e_time
{
	SECONDS,
	MILISECONDS,
	MICROSECONDS,
}						t_time;

typedef enum			e_philosopher_status
{
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}						t_philosopher_status;

// declaration for compiling
typedef struct			s_table t_table;

typedef struct			s_forks
{
	t_mutex				fork;
	int					fork_id;
}						t_forks;

typedef struct			s_philosophers
{
	int					id;
	long				time_last_eat;
	long				meals_count;
	bool				full;
	t_forks				*left_fork;
	t_forks				*right_fork;
	t_table				*table;
	pthread_t			thread_id;
	t_mutex				*philosopher_mutex;
}						t_philosophers;

// ./philosophers 5 800 200 200 [5]
// number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_to_full]
typedef struct			s_table
{
	long				number_of_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_to_full;
	bool				everyone_ready;
	long				start;
	bool				finish;
	t_forks				*fork;
	t_philosophers		*philosopher;
	t_mutex				table_mutex;
	t_mutex				printing_lock_mutex;
}						t_table;

// copy_paste.c
bool					copy_bool(t_mutex *mutex, bool *value);
void					paste_bool(t_mutex *mutex, bool *dst, bool value);
long					copy_long(t_mutex *mutex, long *value);
void					paste_long(t_mutex *mutex, long *dst, long value);

// initializing.c
void					initialize(t_table *table);

// parsing.c
void					parsing(t_table *table, char **argv);


// start_simulation.c
void					*dining(void *data);
void					wait_for_everyone(t_table *table);
void					start_simulation(t_table table);

// status_actions.c

// status_printing.c
void	print_status(t_philosopher_status status, t_philosophers *philosopher, 
	bool bugs);

// thread_mutex.c
void					safe_mutex(t_mutex *mutex, t_code code);
void					safe_thread(t_thread *thread, void *(*ops)(void *),
							void *data, t_code code);

// utilities.c
void					return_error(const char *error_msg);
void					*safe_malloc(size_t bytes);
bool					finished_simulation(t_table *table);
long					get_time(t_time time);
void					better_usleep(long microseconds, t_table *table);

#endif
