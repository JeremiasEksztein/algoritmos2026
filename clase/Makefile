CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c89 -g -fsanitize=address,undefined

all: *.c
	$(CC) $(CFLAGS) $^

clean:
	rm -f a.out

.PHONY:	all clean
