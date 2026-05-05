CC = gcc
CFLAGS = -Wall -Werror -std=c89 -g -pedantic -fsanitize=address

all: *.c
	$(CC) $(CFLAGS) $^ -o test

lib: array_stack.c linked_stack.c
	$(CC) $(CFLAGS) $^ -c
	ar *.o libstack.a

clean: 
	rm -f test
	rm -f *.o
