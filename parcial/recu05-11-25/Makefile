CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c89 -pedantic -g -fsanitize=address,undefined

all: *.c
	$(CC) $(CFLAGS) $^

clean:
	rm -f a.out 
	rm -f ingresos.txt
	rm -f egresos.txt
	rm -f anomalias.txt
	rm -f estado_almacen.txt

.PHONY: all clean
