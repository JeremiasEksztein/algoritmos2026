CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c89 -pedantic -g -fsanitize=address,undefined

all: *.c
	$(CC) $(CFLAGS) $^

test:
	./a.out
	echo 'Ingresos.txt'
	cat ingresos.txt
	cat egresos.txt
	cat anomalias.txt
	cat estado_almacen.txt

clean:
	rm -f a.out 
	rm -f ingresos.txt
	rm -f egresos.txt
	rm -f anomalias.txt
	rm -f estado_almacen.txt

.PHONY: all clean
