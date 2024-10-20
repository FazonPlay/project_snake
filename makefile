CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lSDL2 -lSDL2_image
SOURCES = snake.c test.c
HEADERS = snake.h
OBJECTS = $(SOURCES:.c=.o)
EXEC = snake_game

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c $< $(CFLAGS)

fclean: 
	rm -f $(OBJECTS) $(EXEC)

re: fclean all