CC = gcc
CFLAGS = -Wall -Werror -std=c89 -g -pedantic -fsanitize=address

all: *.c
	$(CC) $(CFLAGS) $^ -o test

clean: 
	rm -f test
