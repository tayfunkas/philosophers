NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -rf

SOURCES = main.c \
	activities.c \
	initialize.c \
	helpers.c \
	checks.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -lpthread

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(NAME)

re: fclean all

PHONY: all clean fclean re
