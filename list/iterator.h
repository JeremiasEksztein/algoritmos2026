#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef int (*next_fn)(void *state);

typedef struct Iterator {
	void *state;
	next_fn next;
} Iterator;

int iter_search(Iterator *iter, const void *key);

#endif 
