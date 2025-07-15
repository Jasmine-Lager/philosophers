CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread # -pthread necesary for mutex & threads

SRCS = \
	main.c \
	parsing.c \
	initilizing.c \
	copy_paste.c \
	thread_mutex.c \
	status_printing.c \
	start_simulation.c \
	utilities.c

OBJS = $(SRCS:.c=.o)

NAME = philosophers

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
