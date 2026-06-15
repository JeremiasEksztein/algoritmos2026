CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c89 -pedantic -g -fsanitize=address,undefined

all:
	$(CC) $(CFLAGS) *.c

clean:
	rm -f a.out

.PHONY:	all	clean
