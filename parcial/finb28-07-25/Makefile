CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c89 -pedantic -g -fsanitize=address,undefined

ej1:
	$(CC) -DEJ1 $(CFLAGS) *.c

clean:
	rm -f a.out

.PHONY: all clean
