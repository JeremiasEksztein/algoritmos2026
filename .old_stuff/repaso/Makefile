CC = gcc
CFLAGS = -Wall -Werror -g -o3 -std=c89 -pedantic

TARGET = test

static: main.c static_vector.c
	$(CC) $(CFLAGS) $^ -DSTATIC_TEST -o $(TARGET)

dynamic: main.c dynamic_vector.c
	$(CC) $(CFLAGS) $^ -DDYNAMIC_TEST -o $(TARGET)

clean: 
	rm -f $(TARGET)
