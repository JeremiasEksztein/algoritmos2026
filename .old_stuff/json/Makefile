CC = gcc
CFLAGS = -Wall -Werror -std=c89 -pedantic -fsanitize=address

all: *.c
	$(CC) $(CFLAGS) $^ -o json

clean:
	rm -f json

.PHONY	all	clean
