CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread # -pthread necesary for mutex & threads

SRCS = \
	copy_paste.c \
	customer_service.c \
	initilizing.c \
	main.c \
	parsing.c \
	print_status.c \
	start_simulation.c \
	thread_mutex.c \
	utilities.c

OBJS = $(SRCS:.c=.o)

NAME = philosophers

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
