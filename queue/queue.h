#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define QUEUE_SIZE 256

#define OK 0
#define ERR 1

typedef enum Bool {
	TRUE = 1,
	FALSE = 0,
	INVALID = -1
} Bool;

typedef struct {
	char buf[QUEUE_SIZE];
	int head;
	int tail;
	size_t n;
} Queue;

int queue_new(Queue* q);

int queue_add(Queue* q, const void* elem, size_t n);

int queue_rem(Queue* q, void* buf, size_t n);

int queue_first(const Queue* q, void* buf, size_t n);

Bool queue_is_empty(const Queue* q);

Bool queue_is_full(const Queue* q, size_t n);

void queue_destroy(Queue* q);

#endif /* QUEUE_H */
