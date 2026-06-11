CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c89 -pedantic -fsanitize=address,undefined

all: main.c alumno.c
	$(CC) $(CFLAGS) $^ && ./a.out

clean:
	rm -f a.out

.PHONY:	all	clean
