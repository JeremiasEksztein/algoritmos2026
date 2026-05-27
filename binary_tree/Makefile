CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c89 -g -fsanitize=address,undefined

all:
	$(CC) $(CFLAGS) *.c -o test

clean:
	rm -f test
