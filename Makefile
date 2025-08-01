CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread # -pthread necesary for mutex & threads
# -g -fsanitize=address -fno-omit-frame-pointer # is 
SRCS = \
	customer_service.c \
	get_set_go.c \
	initilizing.c \
	main.c \
	parsing.c \
	print_status.c \
	safe_thread_mutex_malloc.c \
	simulation_one.c \
	start_simulation.c \
	utilities.c

OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(MAKE) clean

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
