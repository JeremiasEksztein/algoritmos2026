CC = gcc 
CFLAGS = -Wall -Werror -g -pedantic -fsanitize=address -std=c89

all: main.c linked_list.c
	$(CC) $(CFLAGS) $^ -o test

clean:
	rm -f test
