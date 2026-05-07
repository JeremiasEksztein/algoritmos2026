CC = gcc
CFLAGS = -Wall -Werror g- -std=c89 -pedantic -fsanitize=address

all: *.c
	$(CC) $(CFLAGS) $^ -o test

clean:
	rm -f test
