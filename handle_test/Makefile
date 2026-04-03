CC = gcc
CFLAGS = -Wall -Werror -g -o3 -pedantic -std=c89
TARGET = test

static: main.c static_vec.c
	$(CC) $(CFLAGS) $^ -o $(TARGET)

dynamic: main.c dynamic_vec.c
	$(CC) $(CFLAGS) $^ -o $(TARGET)

clean:
	rm -f $(TARGET)
