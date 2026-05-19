CC = gcc
CFLAGS = -Wall -Werror -std=c89 -pedantic -fsanitize=address

static: main.c static_stack.c
	$(CC) $(CFLAGS) $^ -o test

dynamic: main.c dyn_stack.c
	$(CC) $(CFLAGS) $^ -o test

clean:
	rm -f test
