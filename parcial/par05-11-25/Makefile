CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c89 -pedantic -fsanitize=address,undefined

all:
	$(CC) $(CFLAGS) *.c

clean:
	rm -f a.out claves_nuevas.txt

.PHONY: all clean
