CC = gcc
CFLAGS = -Wall -Werror -g -o3 -std=c89 -pedantic -fsanitize=address
TARGET = test

all: *.[ch]
	$(CC) $(CFLAGS) $^ -o $(TARGET)

clean:
	rm -f $(TARGET)
